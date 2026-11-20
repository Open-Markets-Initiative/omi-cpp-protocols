// Jpx.TseEquities.MarketByOrder.Flex.v1.1: types/Price.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <optional>
#include "../cache/Required.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// price
struct price {

    static constexpr const char* name = "price";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = true;
    static constexpr std::uint64_t null_value = 18446744073709551615ULL;
    static constexpr int exponent = -4;

    using result_type = std::optional<std::uint64_t>;
    using storage_type = result_type;

    price()
     : value{ static_cast<std::uint64_t>(__builtin_bswap64(null_value)) } {}

    price(std::uint64_t v)
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

    void set_null() {
        value = static_cast<std::uint64_t>(__builtin_bswap64(null_value));
    }

  protected:
    std::uint64_t value;
};
}
