#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Sequence number of the last packet to be retransmitted
struct EndSequenceNumber {

    static constexpr const char* name = "End Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr EndSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of EndSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
