#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// market_data_group
struct market_data_group {

    static constexpr const char* name = "market_data_group";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr market_data_group()
     : value{ 0 } {}

    constexpr market_data_group(char v)
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
