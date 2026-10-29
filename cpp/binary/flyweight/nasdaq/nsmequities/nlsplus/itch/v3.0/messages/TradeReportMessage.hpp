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

// Relays Nasdaq execution system and Trf trade transactions reported for the current business
// day. Nasdaq reports only one side of a trade execution on the Nls Plus feed.
class TradeReportMessage {
  public:
    static constexpr const char* name = "TradeReportMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeReportMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeReportMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    OriginatingMarketCenterIdentifier originating_market_center_identifier() const { return static_cast<OriginatingMarketCenterIdentifier>(wire::read_char(at(0))); }

    std::string_view issue_symbol() const { return view::text(at(1), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(9))); }

    std::string_view trade_control_number() const { return view::text(at(10), 10, ' '); }

    Decimal trade_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(20))), -4); }

    std::uint32_t trade_size() const { return wire::read_u32_be(at(24)); }

    SaleConditionModifier sale_condition_modifier() const { return SaleConditionModifier{ bytes_.subspan(28) }; }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(32)); }

    void print(std::ostream& out) const {
        out << "TradeReportMessage{";
        out << "originating_market_center_identifier=";
        out << originating_market_center_identifier();
        out << ", issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", trade_control_number=";
        print::text(out, trade_control_number());
        out << ", trade_price=";
        out << trade_price();
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

inline std::ostream& operator<<(std::ostream& out, const TradeReportMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
