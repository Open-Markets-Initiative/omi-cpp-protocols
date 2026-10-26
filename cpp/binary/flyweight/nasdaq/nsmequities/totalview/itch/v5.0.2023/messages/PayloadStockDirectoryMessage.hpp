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
#include "../enums/IssueSubType.hpp"
#include "../enums/Authenticity.hpp"
#include "../enums/ShortSaleThresholdIndicator.hpp"
#include "../enums/IpoFlag.hpp"
#include "../enums/LuldReferencePriceTier.hpp"
#include "../enums/EtpFlag.hpp"
#include "../enums/InverseIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Market data redistributors should process this message to populate the Financial Status
// Indicator (required display field) and the Market Category (recommended display field) for
// NASDAQ-listed issues.
class PayloadStockDirectoryMessage {
  public:
    static constexpr const char* name = "PayloadStockDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PayloadStockDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PayloadStockDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 38;
    static constexpr std::size_t fixed_size = 38;
    std::size_t encoded_size() const { return 38; }

    std::uint16_t stock_locate() const { return wire::read_u16_be(at(0)); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(2)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(4)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::string_view stock() const { return view::text(at(10), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(18))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(19))); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(20)); }

    RoundLotsOnly round_lots_only() const { return static_cast<RoundLotsOnly>(wire::read_char(at(24))); }

    IssueClassification issue_classification() const { return static_cast<IssueClassification>(wire::read_char(at(25))); }

    std::string_view issue_sub_type() const { return view::text(at(26), 2, ' '); }

    Authenticity authenticity() const { return static_cast<Authenticity>(wire::read_char(at(28))); }

    ShortSaleThresholdIndicator short_sale_threshold_indicator() const { return static_cast<ShortSaleThresholdIndicator>(wire::read_char(at(29))); }

    IpoFlag ipo_flag() const { return static_cast<IpoFlag>(wire::read_char(at(30))); }

    LuldReferencePriceTier luld_reference_price_tier() const { return static_cast<LuldReferencePriceTier>(wire::read_char(at(31))); }

    EtpFlag etp_flag() const { return static_cast<EtpFlag>(wire::read_char(at(32))); }

    std::uint32_t etp_leverage_factor() const { return wire::read_u32_be(at(33)); }

    InverseIndicator inverse_indicator() const { return static_cast<InverseIndicator>(wire::read_char(at(37))); }

    void print(std::ostream& out) const {
        out << "PayloadStockDirectoryMessage{";
        out << "stock_locate=";
        out << stock_locate();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
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
        out << ", issue_sub_type=";
        print::text(out, issue_sub_type());
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

inline std::ostream& operator<<(std::ostream& out, const PayloadStockDirectoryMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
