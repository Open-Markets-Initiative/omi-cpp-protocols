#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// pt_mod_flags
struct pt_mod_flags {

    using type = uint8_t;

    static constexpr type canc = type{1} << 0;
    static constexpr type amnd = type{1} << 1;

    static constexpr const char* name = "pt_mod_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr pt_mod_flags()
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

    [[nodiscard]] constexpr bool has_canc() const { return has(canc); }
    [[nodiscard]] constexpr bool has_amnd() const { return has(amnd); }

    constexpr void set_canc(bool v) { set(canc, v); }
    constexpr void set_amnd(bool v) { set(amnd, v); }

  protected:
    type value;
};
}
