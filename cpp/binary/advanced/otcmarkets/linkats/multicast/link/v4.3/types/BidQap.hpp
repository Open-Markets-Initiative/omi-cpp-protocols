// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/BidQap.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// bid_qap
struct bid_qap {

    static constexpr const char* name = "bid_qap";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<std::int8_t>;
    using storage_type = result_type;

    constexpr bid_qap()
     : value{ 0 } {}

    constexpr bid_qap(std::int8_t v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(std::int8_t v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(0);
    }

  protected:
    std::int8_t value;
};
}
