#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// price
struct price {

    static constexpr const char* name = "price";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -4;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr price()
     : value{ 0 } {}

    price(std::int32_t v)
     : value{ static_cast<std::int32_t>(__builtin_bswap32(v)) } {}

    [[nodiscard]] result_type get() const {
        return result_type{static_cast<std::int32_t>(__builtin_bswap32(value))};
    }

    void set(std::int32_t v) {
        value = __builtin_bswap32(v);
    }

    void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int32_t value;
};
}
