// Databento.MarketData.Normalized.Dbn.v3: types/ChannelId.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {


// The channel ID assigned by Databento as an incrementing integer starting at zero
struct ChannelId {

    static constexpr auto name = "Channel Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ChannelId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ChannelId(const std::uint8_t &value)
     : value{ value } {}

    // get value of ChannelId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
