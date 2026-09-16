#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// best_bid
struct best_bid {

    static constexpr const char* name = "best_bid";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr best_bid()
     : value{ 0 } {}

    best_bid(std::uint64_t v)
     : value{ static_cast<std::uint64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::uint64_t>(__builtin_bswap64(value))};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::uint64_t value;
};
}
