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
#include "../structs/SaleConditionModifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Trade Report carrying an eight byte trade price, used when the price breaches the maximum
// value the four byte form can carry.
class LongFormTradeReportMessage {
  public:
    static constexpr const char* name = "LongFormTradeReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit LongFormTradeReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every LongFormTradeReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    OriginatingMarketCenterIdentifier originating_market_center_identifier() const { return static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(at(0))); }

    std::string_view issue_symbol() const { return view::text(at(1), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(9))); }

    std::string_view trade_control_number() const { return view::text(at(10), 10, ' '); }

    Decimal trade_price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_be(at(20))), -4); }

    std::uint32_t trade_size() const { return wire::read_u32_be(at(28)); }

    SaleConditionModifier sale_condition_modifier() const { return SaleConditionModifier{ bytes_.subspan(32) }; }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(36)); }

    void print(std::ostream& out) const {
        out << "LongFormTradeReportMessage{";
        out << "originating_market_center_identifier=";
        out << originating_market_center_identifier();
        out << ", issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", trade_control_number=";
        print::text(out, trade_control_number());
        out << ", trade_price_long=";
        out << trade_price_long();
        out << ", trade_size=";
        out << trade_size();
        out << ", sale_condition_modifier=";
        sale_condition_modifier().print(out);
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const LongFormTradeReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
