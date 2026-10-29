#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Contains the number of shares traded at the Participant’s close price and taking place after the close of a Participant’s regular session.
struct CrossingSessionITotalTradesVolume {

    static constexpr const char* name = "Crossing Session I Total Trades Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CrossingSessionITotalTradesVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossingSessionITotalTradesVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CrossingSessionITotalTradesVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
