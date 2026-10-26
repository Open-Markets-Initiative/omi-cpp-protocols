#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant total volume of shares traded. Has implied 6 decimal places
struct ParticipantFractionalTotalVolume {

    static constexpr const char* name = "Participant Fractional Total Volume";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr ParticipantFractionalTotalVolume()
     : value{ 0 } {}

    // constructor for ParticipantFractionalTotalVolume field
    constexpr explicit ParticipantFractionalTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ParticipantFractionalTotalVolume field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ParticipantFractionalTotalVolume field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
