#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Original sequence number from the live feed.
struct SequenceNumber {

    static constexpr const char* name = "Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr SequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of SequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
