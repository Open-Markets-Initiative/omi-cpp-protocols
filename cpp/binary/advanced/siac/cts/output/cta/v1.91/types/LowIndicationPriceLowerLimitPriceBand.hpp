#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// low_indication_price_lower_limit_price_band
struct low_indication_price_lower_limit_price_band {

    static constexpr const char* name = "low_indication_price_lower_limit_price_band";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;
    static constexpr int exponent = -6;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr low_indication_price_lower_limit_price_band()
     : value{ 0 } {}

    low_indication_price_lower_limit_price_band(std::uint64_t v)
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
