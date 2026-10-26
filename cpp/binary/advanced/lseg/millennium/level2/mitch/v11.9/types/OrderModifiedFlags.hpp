#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdint>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// order_modified_flags
struct order_modified_flags {

    using type = uint8_t;

    static constexpr type priority_flag = type{1} << 0;
    static constexpr type firm_quote = type{1} << 5;

    static constexpr const char* name = "order_modified_flags";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<uint8_t>;
    using storage_type = result_type;

    constexpr order_modified_flags()
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

    [[nodiscard]] constexpr bool has_priority_flag() const { return has(priority_flag); }
    [[nodiscard]] constexpr bool has_firm_quote() const { return has(firm_quote); }

    constexpr void set_priority_flag(bool v) { set(priority_flag, v); }
    constexpr void set_firm_quote(bool v) { set(firm_quote, v); }

  protected:
    type value;
};
}
