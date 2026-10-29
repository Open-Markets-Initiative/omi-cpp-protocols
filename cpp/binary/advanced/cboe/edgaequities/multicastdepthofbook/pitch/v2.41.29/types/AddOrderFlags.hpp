#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

// add_order_flags
struct add_order_flags {

    using type = uint8_t;

    static constexpr type display = type{1} << 0;

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

    [[nodiscard]] constexpr bool has_display() const { return has(display); }

    constexpr void set_display(bool v) { set(display, v); }

  protected:
    type value;
};
}
