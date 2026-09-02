#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// reserved_1
struct reserved_1 {

    static constexpr const char* name = "reserved_1";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr reserved_1()
     : value{ 0 } {}

    constexpr reserved_1(char v)
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
