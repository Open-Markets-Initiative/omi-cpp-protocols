#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// trade_condition
struct trade_condition {

    using type = uint16_t;

    static constexpr type opening_price = type{1} << 0;
    static constexpr type crossed = type{1} << 1;
    static constexpr type last_trade_at_the_same_price = type{1} << 2;
    static constexpr type out_of_sequence = type{1} << 3;
    static constexpr type trade_on_behalf = type{1} << 6;
    static constexpr type regular_trade = type{1} << 13;
    static constexpr type block_trade = type{1} << 14;

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<uint16_t>;
    using storage_type = result_type;

    constexpr trade_condition()
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

    [[nodiscard]] constexpr bool has_opening_price() const { return has(opening_price); }
    [[nodiscard]] constexpr bool has_crossed() const { return has(crossed); }
    [[nodiscard]] constexpr bool has_last_trade_at_the_same_price() const { return has(last_trade_at_the_same_price); }
    [[nodiscard]] constexpr bool has_out_of_sequence() const { return has(out_of_sequence); }
    [[nodiscard]] constexpr bool has_trade_on_behalf() const { return has(trade_on_behalf); }
    [[nodiscard]] constexpr bool has_regular_trade() const { return has(regular_trade); }
    [[nodiscard]] constexpr bool has_block_trade() const { return has(block_trade); }

    constexpr void set_opening_price(bool v) { set(opening_price, v); }
    constexpr void set_crossed(bool v) { set(crossed, v); }
    constexpr void set_last_trade_at_the_same_price(bool v) { set(last_trade_at_the_same_price, v); }
    constexpr void set_out_of_sequence(bool v) { set(out_of_sequence, v); }
    constexpr void set_trade_on_behalf(bool v) { set(trade_on_behalf, v); }
    constexpr void set_regular_trade(bool v) { set(regular_trade, v); }
    constexpr void set_block_trade(bool v) { set(block_trade, v); }

  protected:
    type value;
};
}
