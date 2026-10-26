#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v8 {

// settl_price_type
struct settl_price_type {

    using type = uint8_t;

    static constexpr type final = type{1} << 0;
    static constexpr type actual = type{1} << 1;
    static constexpr type rounded = type{1} << 2;
    static constexpr type intraday = type{1} << 3;
    static constexpr type null_value = type{1} << 7;

    static constexpr const char* name = "settl_price_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr settl_price_type()
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

    [[nodiscard]] constexpr bool has_final() const { return has(final); }
    [[nodiscard]] constexpr bool has_actual() const { return has(actual); }
    [[nodiscard]] constexpr bool has_rounded() const { return has(rounded); }
    [[nodiscard]] constexpr bool has_intraday() const { return has(intraday); }
    [[nodiscard]] constexpr bool has_null_value() const { return has(null_value); }

    constexpr void set_final(bool v) { set(final, v); }
    constexpr void set_actual(bool v) { set(actual, v); }
    constexpr void set_rounded(bool v) { set(rounded, v); }
    constexpr void set_intraday(bool v) { set(intraday, v); }
    constexpr void set_null_value(bool v) { set(null_value, v); }

  protected:
    type value;
};
}
