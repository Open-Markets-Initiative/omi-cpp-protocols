#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_10 {

// Contains the Dollar Value traded after the close of a Participant’s regular session.
struct CrossingSessionIiDollarValue {

    static constexpr const char* name = "Crossing Session Ii Dollar Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr CrossingSessionIiDollarValue()
     : value{ 0 } {}

    // constructor for CrossingSessionIiDollarValue field
    constexpr explicit CrossingSessionIiDollarValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of CrossingSessionIiDollarValue field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of CrossingSessionIiDollarValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
