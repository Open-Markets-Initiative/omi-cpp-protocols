#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cme::mdp3::v5 {

// md_entry_px
struct md_entry_px {

    static constexpr const char* name = "md_entry_px";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -7;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr md_entry_px()
     : value{ 0 } {}

    constexpr md_entry_px(std::int64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
