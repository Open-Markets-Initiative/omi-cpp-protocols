#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketCenter.hpp"
#include "../enums/SecurityClass.hpp"
#include "../common/Decimal.hpp"
#include "../structs/OriginalSaleConditionModifier.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates that a previously reported NextShares trade transaction has been cancelled or was
// reported in error.
class NextSharesTradeCancelErrorMessage {
  public:
    static constexpr const char* name = "NextSharesTradeCancelErrorMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit NextSharesTradeCancelErrorMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every NextSharesTradeCancelErrorMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 44;
    static constexpr std::size_t fixed_size = 44;
    std::size_t encoded_size() const { return 44; }

    MarketCenter market_center() const { return static_cast<MarketCenter>(wire::read_char(at(0))); }

    std::string_view issue_symbol() const { return view::text(at(1), 8, ' '); }

    SecurityClass security_class() const { return static_cast<SecurityClass>(wire::read_char(at(9))); }

    std::string_view original_trade_control_number() const { return view::text(at(10), 10, ' '); }

    Decimal original_proxy_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(20))), -4); }

    Decimal original_nav_offset_amount() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(24))), -4); }

    std::uint32_t original_trade_size() const { return wire::read_u32_be(at(28)); }

    OriginalSaleConditionModifier original_sale_condition_modifier() const { return OriginalSaleConditionModifier{ bytes_.subspan(32) }; }

    std::uint64_t consolidated_volume() const { return wire::read_u64_be(at(36)); }

    void print(std::ostream& out) const {
        out << "NextSharesTradeCancelErrorMessage{";
        out << "market_center=";
        out << market_center();
        out << ", issue_symbol=";
        print::text(out, issue_symbol());
        out << ", security_class=";
        out << security_class();
        out << ", original_trade_control_number=";
        print::text(out, original_trade_control_number());
        out << ", original_proxy_price=";
        out << original_proxy_price();
        out << ", original_nav_offset_amount=";
        out << original_nav_offset_amount();
        out << ", original_trade_size=";
        out << original_trade_size();
        out << ", original_sale_condition_modifier=";
        original_sale_condition_modifier().print(out);
        out << ", consolidated_volume=";
        out << consolidated_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const NextSharesTradeCancelErrorMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
