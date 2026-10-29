#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// net_chg_prev_day_mantissa
struct net_chg_prev_day_mantissa {

    static constexpr const char* name = "net_chg_prev_day_mantissa";
    static constexpr std::size_t size = 4;
    static constexpr bool is_optional = false;

    using result_type = required<std::int32_t>;
    using storage_type = result_type;

    constexpr net_chg_prev_day_mantissa()
     : value{ 0 } {}

    net_chg_prev_day_mantissa(std::int32_t v)
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
