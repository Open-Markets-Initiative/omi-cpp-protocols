#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/MarketCategory.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/RoundLotsOnly.hpp"
#include "../enums/IssueClassification.hpp"
#include "../enums/IssueSubtype.hpp"
#include "../enums/Authenticity.hpp"
#include "../enums/ShortSaleThresholdIndicator.hpp"
#include "../enums/IpoFlag.hpp"
#include "../enums/LuldReferencePriceTier.hpp"
#include "../enums/EtpFlag.hpp"
#include "../enums/InverseIndicator.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// At the start of each trading day, Nasdaq disseminates stock directory messages for all
// active symbols in its market center system.
class StockDirectoryMessage {
  public:
    static constexpr const char* name = "StockDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 36;
    static constexpr std::size_t fixed_size = 36;
    std::size_t encoded_size() const { return 36; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds time_stamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t time_stamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time_stamp().count())); }

    std::string_view stock() const { return view::text(at(8), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(16))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(17))); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(18)); }

    RoundLotsOnly round_lots_only() const { return static_cast<RoundLotsOnly>(wire::read_char(at(22))); }

    IssueClassification issue_classification() const { return static_cast<IssueClassification>(wire::read_char(at(23))); }

    std::string_view issue_subtype() const { return view::text(at(24), 2, ' '); }

    Authenticity authenticity() const { return static_cast<Authenticity>(wire::read_char(at(26))); }

    ShortSaleThresholdIndicator short_sale_threshold_indicator() const { return static_cast<ShortSaleThresholdIndicator>(wire::read_char(at(27))); }

    IpoFlag ipo_flag() const { return static_cast<IpoFlag>(wire::read_char(at(28))); }

    LuldReferencePriceTier luld_reference_price_tier() const { return static_cast<LuldReferencePriceTier>(wire::read_char(at(29))); }

    EtpFlag etp_flag() const { return static_cast<EtpFlag>(wire::read_char(at(30))); }

    std::uint32_t etp_leverage_factor() const { return wire::read_u32_be(at(31)); }

    InverseIndicator inverse_indicator() const { return static_cast<InverseIndicator>(wire::read_char(at(35))); }

    void print(std::ostream& out) const {
        out << "StockDirectoryMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", time_stamp=";
        calendar::print(out, time_stamp().count(), 1, "America/New_York");
        out << ", stock=";
        print::text(out, stock());
        out << ", market_category=";
        out << market_category();
        out << ", financial_status_indicator=";
        out << financial_status_indicator();
        out << ", round_lot_size=";
        out << round_lot_size();
        out << ", round_lots_only=";
        out << round_lots_only();
        out << ", issue_classification=";
        out << issue_classification();
        out << ", issue_subtype=";
        print::text(out, issue_subtype());
        out << ", authenticity=";
        out << authenticity();
        out << ", short_sale_threshold_indicator=";
        out << short_sale_threshold_indicator();
        out << ", ipo_flag=";
        out << ipo_flag();
        out << ", luld_reference_price_tier=";
        out << luld_reference_price_tier();
        out << ", etp_flag=";
        out << etp_flag();
        out << ", etp_leverage_factor=";
        out << etp_leverage_factor();
        out << ", inverse_indicator=";
        out << inverse_indicator();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const StockDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
