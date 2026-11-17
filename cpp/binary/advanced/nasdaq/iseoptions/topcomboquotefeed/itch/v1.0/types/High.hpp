// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0: types/High.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// high
struct high {

    static constexpr const char* name = "high";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -8;

    using result_type = required<std::int64_t>;
    using storage_type = result_type;

    constexpr high()
     : value{ 0 } {}

    high(std::int64_t v)
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
