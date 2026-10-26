#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the Participant Total Volume of shares traded for a security at the time of the trade correction or cancel/error
struct ParticipantTotalVolume {

    static constexpr const char* name = "Participant Total Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ParticipantTotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantTotalVolume(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ParticipantTotalVolume field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
