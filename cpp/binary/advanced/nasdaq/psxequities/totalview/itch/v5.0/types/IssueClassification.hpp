#pragma once

#include <cstddef>
#include "../cache/Required.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

// issue_classification
struct issue_classification {

    static constexpr const char* name = "issue_classification";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<char>;
    using storage_type = result_type;

    constexpr issue_classification()
     : value{ 0 } {}

    constexpr issue_classification(char v)
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
