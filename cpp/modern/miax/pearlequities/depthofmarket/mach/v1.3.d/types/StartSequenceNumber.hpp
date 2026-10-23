#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Sequence number of the first packet to be retransmitted
struct StartSequenceNumber {

    static constexpr const char* name = "Start Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr StartSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StartSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of StartSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
