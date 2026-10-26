#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// data_feed_indicator
struct data_feed_indicator {

    static constexpr const char* name = "data_feed_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr data_feed_indicator()
     : value{ 0 } {}

    constexpr data_feed_indicator(char v)
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
