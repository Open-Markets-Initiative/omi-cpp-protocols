#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace cme::mdp3::v13 {

// broken_date_term_type
struct broken_date_term_type {

    static constexpr const char* name = "broken_date_term_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = true;
    static constexpr std::uint8_t null_value = 255;

    using result_type = std::optional<std::uint8_t>;
    using storage_type = result_type;

    constexpr broken_date_term_type()
     : value{ 0 } {}

    constexpr broken_date_term_type(std::uint8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::uint8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint8_t value;
};
}
