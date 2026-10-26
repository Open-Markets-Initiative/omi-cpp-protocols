#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

// extension_number
struct extension_number {

    static constexpr const char* name = "extension_number";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr extension_number()
     : value{ 0 } {}

    constexpr extension_number(char v)
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
