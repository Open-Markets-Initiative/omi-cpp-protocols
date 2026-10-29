#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

// session_state
struct session_state {

    static constexpr const char* name = "session_state";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr session_state()
     : value{ 0 } {}

    constexpr session_state(char v)
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
