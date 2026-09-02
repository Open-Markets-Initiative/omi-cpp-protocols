#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

// sale_condition_flags
struct sale_condition_flags {

    using type = uint8_t;

    static constexpr type singleprice_cross_trade = type{1} << 3;
    static constexpr type trade_through_exempt = type{1} << 4;
    static constexpr type odd_lot = type{1} << 5;
    static constexpr type extended_hours = type{1} << 6;
    static constexpr type intermarket_sweep = type{1} << 7;

    static constexpr const char* name = "sale_condition_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr sale_condition_flags()
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

    [[nodiscard]] constexpr bool has_singleprice_cross_trade() const { return has(singleprice_cross_trade); }
    [[nodiscard]] constexpr bool has_trade_through_exempt() const { return has(trade_through_exempt); }
    [[nodiscard]] constexpr bool has_odd_lot() const { return has(odd_lot); }
    [[nodiscard]] constexpr bool has_extended_hours() const { return has(extended_hours); }
    [[nodiscard]] constexpr bool has_intermarket_sweep() const { return has(intermarket_sweep); }

    constexpr void set_singleprice_cross_trade(bool v) { set(singleprice_cross_trade, v); }
    constexpr void set_trade_through_exempt(bool v) { set(trade_through_exempt, v); }
    constexpr void set_odd_lot(bool v) { set(odd_lot, v); }
    constexpr void set_extended_hours(bool v) { set(extended_hours, v); }
    constexpr void set_intermarket_sweep(bool v) { set(intermarket_sweep, v); }

  protected:
    type value;
};
}
