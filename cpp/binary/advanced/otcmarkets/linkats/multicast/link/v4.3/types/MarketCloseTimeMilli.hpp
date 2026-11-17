// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/MarketCloseTimeMilli.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// market_close_time_milli
struct market_close_time_milli {

    static constexpr const char* name = "market_close_time_milli";
    static constexpr std::size_t size = 8;
    static constexpr bool is_optional = false;

    using result_type = required<std::uint64_t>;
    using storage_type = result_type;

    constexpr market_close_time_milli()
     : value{ 0 } {}

    market_close_time_milli(std::uint64_t v)
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
