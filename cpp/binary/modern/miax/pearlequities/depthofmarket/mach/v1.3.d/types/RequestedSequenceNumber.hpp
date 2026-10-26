#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Specifies client requested sequence number
struct RequestedSequenceNumber {

    static constexpr const char* name = "Requested Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr RequestedSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RequestedSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of RequestedSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
