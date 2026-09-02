#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

// iex_tp_header
struct iex_tp_header {

    static constexpr const char* name = "iex_tp_header";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr iex_tp_header()
     : value{ 0 } {}

    constexpr iex_tp_header(char v)
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
