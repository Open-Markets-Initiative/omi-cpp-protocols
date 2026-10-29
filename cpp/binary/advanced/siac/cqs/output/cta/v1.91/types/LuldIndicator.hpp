#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// luld_indicator
struct luld_indicator {

    static constexpr const char* name = "luld_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr luld_indicator()
     : value{ 0 } {}

    constexpr luld_indicator(char v)
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
