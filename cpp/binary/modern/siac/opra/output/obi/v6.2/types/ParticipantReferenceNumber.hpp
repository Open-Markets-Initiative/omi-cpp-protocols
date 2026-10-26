#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// The PRN is for optional use by the Participant
struct ParticipantReferenceNumber {

    static constexpr const char* name = "Participant Reference Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ParticipantReferenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ParticipantReferenceNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ParticipantReferenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
