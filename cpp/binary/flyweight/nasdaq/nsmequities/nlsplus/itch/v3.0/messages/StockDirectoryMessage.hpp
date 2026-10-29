#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
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

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Identifies the securities eligible for the trading session, disseminated at the start of
// each day.
class StockDirectoryMessage {
  public:
    static constexpr const char* name = "StockDirectoryMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit StockDirectoryMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every StockDirectoryMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::string_view stock() const { return view::text(at(0), 8, ' '); }

    MarketCategory market_category() const { return static_cast<MarketCategory>(wire::read_char(at(8))); }

    FinancialStatusIndicator financial_status_indicator() const { return static_cast<FinancialStatusIndicator>(wire::read_char(at(9))); }

    std::uint32_t round_lot_size() const { return wire::read_u32_be(at(10)); }

    RoundLotsOnly round_lots_only() const { return static_cast<RoundLotsOnly>(wire::read_char(at(14))); }

    IssueClassification issue_classification() const { return static_cast<IssueClassification>(wire::read_char(at(15))); }

    std::string_view issue_sub_type() const { return view::text(at(16), 2, ' '); }

    Authenticity authenticity() const { return static_cast<Authenticity>(wire::read_char(at(18))); }

    ShortSaleThresholdIndicator short_sale_threshold_indicator() const { return static_cast<ShortSaleThresholdIndicator>(wire::read_char(at(19))); }

    IpoFlag ipo_flag() const { return static_cast<IpoFlag>(wire::read_char(at(20))); }

    LuldReferencePriceTier luld_reference_price_tier() const { return static_cast<LuldReferencePriceTier>(wire::read_char(at(21))); }

    EtpFlag etp_flag() const { return static_cast<EtpFlag>(wire::read_char(at(22))); }

    std::uint32_t etp_leverage_factor() const { return wire::read_u32_be(at(23)); }

    InverseIndicator inverse_indicator() const { return static_cast<InverseIndicator>(wire::read_char(at(27))); }

    std::string_view bloomberg_id() const { return view::text(at(28), 12, ' '); }

    void print(std::ostream& out) const {
        out << "StockDirectoryMessage{";
        out << "stock=";
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
        out << ", bloomberg_id=";
        print::text(out, bloomberg_id());
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

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
