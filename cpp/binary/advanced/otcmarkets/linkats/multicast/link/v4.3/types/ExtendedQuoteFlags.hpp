// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ExtendedQuoteFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// extended_quote_flags
struct extended_quote_flags {

    using type = uint8_t;

    static constexpr type quote_saturated = type{1} << 0;
    static constexpr type bid_auto_ex = type{1} << 1;
    static constexpr type offer_auto_ex = type{1} << 2;
    static constexpr type nms_conditional_quote = type{1} << 3;

    static constexpr const char* name = "extended_quote_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr extended_quote_flags()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint8_t v) {
        value = v;
    }

    constexpr void set(result_type v) {
        if (v.has_value())
            set(v.value());
        else
            set(type{0});
    }

    [[nodiscard]] constexpr bool has(type bit) const { return (value & bit) != 0; }
    constexpr void set(type bit, bool enabled) { if (enabled) value |= bit; else value &= static_cast<type>(~bit); }

    [[nodiscard]] constexpr bool has_quote_saturated() const { return has(quote_saturated); }
    [[nodiscard]] constexpr bool has_bid_auto_ex() const { return has(bid_auto_ex); }
    [[nodiscard]] constexpr bool has_offer_auto_ex() const { return has(offer_auto_ex); }
    [[nodiscard]] constexpr bool has_nms_conditional_quote() const { return has(nms_conditional_quote); }

    constexpr void set_quote_saturated(bool v) { set(quote_saturated, v); }
    constexpr void set_bid_auto_ex(bool v) { set(bid_auto_ex, v); }
    constexpr void set_offer_auto_ex(bool v) { set(offer_auto_ex, v); }
    constexpr void set_nms_conditional_quote(bool v) { set(nms_conditional_quote, v); }

  protected:
    type value;
};
}
