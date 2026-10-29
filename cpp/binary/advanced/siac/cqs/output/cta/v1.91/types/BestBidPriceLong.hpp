#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// best_bid_price_long
struct best_bid_price_long {

    static constexpr const char* name = "best_bid_price_long";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -6;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr best_bid_price_long()
     : value{ 0 } {}

    best_bid_price_long(std::uint64_t v)
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
