#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

// ssr_state
struct ssr_state {

    static constexpr const char* name = "ssr_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr ssr_state()
     : value{ 0 } {}

    constexpr ssr_state(char v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(char v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    char value;
};
}
