#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// Contains the number of shares traded after the close of a Participant’s regular session.
struct CrossingSessionIiTotalTradesVolume {

    static constexpr const char* name = "Crossing Session Ii Total Trades Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CrossingSessionIiTotalTradesVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossingSessionIiTotalTradesVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CrossingSessionIiTotalTradesVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
