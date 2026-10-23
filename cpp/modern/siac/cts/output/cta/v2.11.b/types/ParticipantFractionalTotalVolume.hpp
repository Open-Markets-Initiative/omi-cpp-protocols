#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Participant total volume of shares traded. Has implied 6 decimal places
struct ParticipantFractionalTotalVolume {

    static constexpr const char* name = "Participant Fractional Total Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr ParticipantFractionalTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantFractionalTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of ParticipantFractionalTotalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
