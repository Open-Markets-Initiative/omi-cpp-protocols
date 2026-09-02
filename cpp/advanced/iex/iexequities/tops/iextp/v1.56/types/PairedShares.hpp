#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

// paired_shares
struct paired_shares {

    static constexpr const char* name = "paired_shares";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint32_t>;
    using storage_type = result_type;

    constexpr paired_shares()
     : value{ 0 } {}

    constexpr paired_shares(std::uint32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint32_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint32_t value;
};
}
