// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/QuoteFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// quote_flags
struct quote_flags {

    using type = uint8_t;

    static constexpr type update_side = type{1} << 0;
    static constexpr type state = type{1} << 1;
    static constexpr type ask_unsolicited = type{1} << 2;
    static constexpr type ask_priced = type{1} << 3;
    static constexpr type ask_bid_wanted = type{1} << 4;
    static constexpr type bid_unsolicited = type{1} << 5;
    static constexpr type bid_priced = type{1} << 6;
    static constexpr type bid_ask_wanted = type{1} << 7;

    static constexpr const char* name = "quote_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr quote_flags()
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

    [[nodiscard]] constexpr bool has_update_side() const { return has(update_side); }
    [[nodiscard]] constexpr bool has_state() const { return has(state); }
    [[nodiscard]] constexpr bool has_ask_unsolicited() const { return has(ask_unsolicited); }
    [[nodiscard]] constexpr bool has_ask_priced() const { return has(ask_priced); }
    [[nodiscard]] constexpr bool has_ask_bid_wanted() const { return has(ask_bid_wanted); }
    [[nodiscard]] constexpr bool has_bid_unsolicited() const { return has(bid_unsolicited); }
    [[nodiscard]] constexpr bool has_bid_priced() const { return has(bid_priced); }
    [[nodiscard]] constexpr bool has_bid_ask_wanted() const { return has(bid_ask_wanted); }

    constexpr void set_update_side(bool v) { set(update_side, v); }
    constexpr void set_state(bool v) { set(state, v); }
    constexpr void set_ask_unsolicited(bool v) { set(ask_unsolicited, v); }
    constexpr void set_ask_priced(bool v) { set(ask_priced, v); }
    constexpr void set_ask_bid_wanted(bool v) { set(ask_bid_wanted, v); }
    constexpr void set_bid_unsolicited(bool v) { set(bid_unsolicited, v); }
    constexpr void set_bid_priced(bool v) { set(bid_priced, v); }
    constexpr void set_bid_ask_wanted(bool v) { set(bid_ask_wanted, v); }

  protected:
    type value;
};
}
