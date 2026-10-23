#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the Dollar Value traded after the close of a Participant's regular session. Has implied 6 decimal places
struct CrossingSessionIiDollarValue {

    static constexpr const char* name = "Crossing Session Ii Dollar Value";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr CrossingSessionIiDollarValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossingSessionIiDollarValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of CrossingSessionIiDollarValue field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
