// Lseg.Millennium.Level2.Mitch.v11.9: types/AddOrderFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// add_order_flags
struct add_order_flags {

    using type = uint8_t;

    static constexpr type unused_4 = type{0xF} << 0;
    static constexpr type market_order = type{1} << 4;
    static constexpr type unused_1 = type{1} << 5;
    static constexpr type private_rfq = type{1} << 6;
    static constexpr type second_unused_1 = type{1} << 7;

    static constexpr const char* name = "add_order_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr add_order_flags()
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

    [[nodiscard]] constexpr type get_unused_4() const { return static_cast<type>((value & unused_4) >> 0); }
    [[nodiscard]] constexpr bool has_market_order() const { return has(market_order); }
    [[nodiscard]] constexpr bool has_unused_1() const { return has(unused_1); }
    [[nodiscard]] constexpr bool has_private_rfq() const { return has(private_rfq); }
    [[nodiscard]] constexpr bool has_second_unused_1() const { return has(second_unused_1); }

    constexpr void set_unused_4(type v) { const type held = static_cast<type>((value & static_cast<type>(~unused_4)) | ((v << 0) & unused_4)); value = held; }
    constexpr void set_market_order(bool v) { set(market_order, v); }
    constexpr void set_unused_1(bool v) { set(unused_1, v); }
    constexpr void set_private_rfq(bool v) { set(private_rfq, v); }
    constexpr void set_second_unused_1(bool v) { set(second_unused_1, v); }

  protected:
    type value;
};
}
