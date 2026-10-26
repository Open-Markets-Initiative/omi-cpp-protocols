#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// match_algorithm
struct match_algorithm {

    static constexpr const char* name = "match_algorithm";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr match_algorithm()
     : value{ 0 } {}

    constexpr match_algorithm(char v)
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
