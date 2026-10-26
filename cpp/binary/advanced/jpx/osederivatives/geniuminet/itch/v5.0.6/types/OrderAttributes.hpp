#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// order_attributes
struct order_attributes {

    using type = uint16_t;

    static constexpr type force = type{1} << 0;
    static constexpr type short_sell = type{1} << 1;
    static constexpr type market_bid = type{1} << 2;
    static constexpr type price_stabilization = type{1} << 3;
    static constexpr type override_crossing = type{1} << 4;
    static constexpr type undisclosed = type{1} << 5;

    static constexpr const char* name = "order_attributes";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<uint16_t>;
    using storage_type = result_type;

    constexpr order_attributes()
     : value{ 0 } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(uint16_t v) {
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

    [[nodiscard]] constexpr bool has_force() const { return has(force); }
    [[nodiscard]] constexpr bool has_short_sell() const { return has(short_sell); }
    [[nodiscard]] constexpr bool has_market_bid() const { return has(market_bid); }
    [[nodiscard]] constexpr bool has_price_stabilization() const { return has(price_stabilization); }
    [[nodiscard]] constexpr bool has_override_crossing() const { return has(override_crossing); }
    [[nodiscard]] constexpr bool has_undisclosed() const { return has(undisclosed); }

    constexpr void set_force(bool v) { set(force, v); }
    constexpr void set_short_sell(bool v) { set(short_sell, v); }
    constexpr void set_market_bid(bool v) { set(market_bid, v); }
    constexpr void set_price_stabilization(bool v) { set(price_stabilization, v); }
    constexpr void set_override_crossing(bool v) { set(override_crossing, v); }
    constexpr void set_undisclosed(bool v) { set(undisclosed, v); }

  protected:
    type value;
};
}
