#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// end_date
struct end_date {

    static constexpr const char* name = "end_date";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = true;
    static constexpr std::int32_t null_value = 0;

    using result_type = std::optional<std::int32_t>;
    using storage_type = result_type;

    constexpr end_date()
     : value{ 0 } {}

    constexpr end_date(std::int32_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return value == null_value ? std::nullopt : result_type{value};
    }

    constexpr void set(std::int32_t v) {
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
    std::int32_t value;
};
}
