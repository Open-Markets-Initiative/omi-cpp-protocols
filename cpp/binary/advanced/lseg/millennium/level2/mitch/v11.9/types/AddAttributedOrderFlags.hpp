// Lseg.Millennium.Level2.Mitch.v11.9: types/AddAttributedOrderFlags.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// add_attributed_order_flags
struct add_attributed_order_flags {

    using type = uint8_t;

    static constexpr type unused_4 = type{0xF} << 0;
    static constexpr type named_market_order = type{1} << 4;
    static constexpr type firm_quote = type{1} << 5;
    static constexpr type unused_2 = type{0x3} << 6;

    static constexpr const char* name = "add_attributed_order_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr add_attributed_order_flags()
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
    [[nodiscard]] constexpr bool has_named_market_order() const { return has(named_market_order); }
    [[nodiscard]] constexpr bool has_firm_quote() const { return has(firm_quote); }
    [[nodiscard]] constexpr type get_unused_2() const { return static_cast<type>((value & unused_2) >> 6); }

    constexpr void set_unused_4(type v) { const type held = static_cast<type>((value & static_cast<type>(~unused_4)) | ((v << 0) & unused_4)); value = held; }
    constexpr void set_named_market_order(bool v) { set(named_market_order, v); }
    constexpr void set_firm_quote(bool v) { set(firm_quote, v); }
    constexpr void set_unused_2(type v) { const type held = static_cast<type>((value & static_cast<type>(~unused_2)) | ((v << 6) & unused_2)); value = held; }

  protected:
    type value;
};
}
