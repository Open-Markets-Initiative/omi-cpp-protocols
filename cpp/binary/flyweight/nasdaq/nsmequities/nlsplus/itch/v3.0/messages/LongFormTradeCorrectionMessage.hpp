#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/OriginatingMarketCenterIdentifier.hpp"
#include "../enums/SecurityClass.hpp"
#include "../common/Decimal.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"
#include "../structs/CorrectedSaleConditionModifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Trade Correction carrying eight byte original and corrected trade prices.
class LongFormTradeCorrectionMessage {
  public:
    static constexpr const char* name = "LongFormTradeCorrectionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongFormTradeCorrectionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongFormTradeCorrectionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 70;
    static constexpr std::size_t fixed_size = 70;
    std::size_t encoded_size() const { return 70; }

    OriginatingMarketCenterIdentifier originating_market_center_identifier() const { return static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(at(0))); }

    std::string_view issue_symbol() const { return view::text(at(1), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(9))); }

    std::string_view original_trade_control_number() const { return view::text(at(10), 10, ' '); }

    Decimal original_trade_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(20))), -4); }

    std::uint32_t original_trade_size() const { return wire::read_u32_be(at(28)); }

    OriginalSaleConditionModifier original_sale_condition_modifier() const { return OriginalSaleConditionModifier{ bytes_.subspan(32) }; }

    std::string_view corrected_trade_control_number() const { return view::text(at(36), 10, ' '); }

    Decimal corrected_trade_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(46))), -4); }

    std::uint32_t corrected_trade_size() const { return wire::read_u32_be(at(54)); }

    CorrectedSaleConditionModifier corrected_sale_condition_modifier() const { return CorrectedSaleConditionModifier{ bytes_.subspan(58) }; }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(62)); }

    void print(std::ostream& out) const {
        out << "LongFormTradeCorrectionMessage{";
        out << "originating_market_center_identifier=";
        out << originating_market_center_identifier();
        out << ", issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", original_trade_control_number=";
        print::text(out, original_trade_control_number());
        out << ", original_trade_price_long=";
        out << original_trade_price_long();
        out << ", original_trade_size=";
        out << original_trade_size();
        out << ", original_sale_condition_modifier=";
        original_sale_condition_modifier().print(out);
        out << ", corrected_trade_control_number=";
        print::text(out, corrected_trade_control_number());
        out << ", corrected_trade_price_long=";
        out << corrected_trade_price_long();
        out << ", corrected_trade_size=";
        out << corrected_trade_size();
        out << ", corrected_sale_condition_modifier=";
        corrected_sale_condition_modifier().print(out);
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongFormTradeCorrectionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
