#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// alloc_id
struct alloc_id {

    static constexpr const char* name = "alloc_id";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr alloc_id()
     : value{ 0 } {}

    constexpr alloc_id(std::uint64_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::uint64_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
