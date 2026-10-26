#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// body_len
struct body_len {

    static constexpr const char* name = "body_len";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint16_t>;
    using storage_type = result_type;

    constexpr body_len()
     : value{ 0 } {}

    constexpr body_len(std::uint16_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint16_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint16_t value;
};
}
