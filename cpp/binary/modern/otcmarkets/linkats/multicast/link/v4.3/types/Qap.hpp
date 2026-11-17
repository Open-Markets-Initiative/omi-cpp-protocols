// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/Qap.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Specifies the access fee or rebate for the bid/offer. Positive values (1 to 30) indicate a rebate, negative values (-1 to -30) indicate an access fee, and 0 indicates no rebate or access fee.
struct Qap {

    static constexpr auto name = "Qap";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;

    // default constructor
    constexpr Qap()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Qap(const std::int8_t &value)
     : value{ value } {}

    // get value of Qap field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
