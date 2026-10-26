#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_11_b {

// corrected_stop_stock_indicator
struct corrected_stop_stock_indicator {

    static constexpr const char* name = "corrected_stop_stock_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr corrected_stop_stock_indicator()
     : value{ 0 } {}

    constexpr corrected_stop_stock_indicator(char v)
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
