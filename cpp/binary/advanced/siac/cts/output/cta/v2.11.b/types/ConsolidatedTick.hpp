#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// consolidated_tick
struct consolidated_tick {

    static constexpr const char* name = "consolidated_tick";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr consolidated_tick()
     : value{ 0 } {}

    constexpr consolidated_tick(char v)
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
