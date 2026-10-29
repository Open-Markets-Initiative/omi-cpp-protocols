#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// original_participant_reference_number
struct original_participant_reference_number {

    static constexpr const char* name = "original_participant_reference_number";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr original_participant_reference_number()
     : value{ 0 } {}

    original_participant_reference_number(std::int64_t v)
     : value{ static_cast<std::int64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::int64_t>(__builtin_bswap64(value))};
    }

    void set(std::int64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int64_t value;
};
}
