#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// third_reserved
struct third_reserved {

    static constexpr const char* name = "third_reserved";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr third_reserved()
     : value{ 0 } {}

    constexpr third_reserved(char v)
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
