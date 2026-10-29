#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// auction_collar_lower_threshold_price
struct auction_collar_lower_threshold_price {

    static constexpr const char* name = "auction_collar_lower_threshold_price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 0ULL;
    static constexpr int exponent = -6;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    constexpr auction_collar_lower_threshold_price()
     : value{ 0 } {}

    auction_collar_lower_threshold_price(std::uint64_t v)
     : value{ static_cast<std::uint64_t>(__builtin_bswap64(v)) } {}

    [[nodiscard]] result_type get() const {
        auto host = static_cast<std::uint64_t>(__builtin_bswap64(value));
        return host == null_value ? std::nullopt : result_type{host};
    }

    void set(std::uint64_t v) {
        value = __builtin_bswap64(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(null_value);
    }

    constexpr void set_null() {
        value = null_value;
    }

  protected:
    std::uint64_t value;
};
}
