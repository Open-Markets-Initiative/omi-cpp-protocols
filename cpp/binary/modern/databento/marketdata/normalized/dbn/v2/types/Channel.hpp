// Databento.MarketData.Normalized.Dbn.v2: types/Channel.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v2 {

// The channel ID assigned by Databento as an incrementing integer starting at zero
struct Channel {

    static constexpr const char* name = "Channel";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Channel()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Channel(const std::uint16_t value)
     : value{ value } {}

    // get value of Channel field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
