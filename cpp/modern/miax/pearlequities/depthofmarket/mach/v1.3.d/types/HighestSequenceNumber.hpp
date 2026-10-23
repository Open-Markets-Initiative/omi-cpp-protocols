#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// the highest sequence number that the server currently has for the client
struct HighestSequenceNumber {

    static constexpr const char* name = "Highest Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr HighestSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HighestSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of HighestSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
