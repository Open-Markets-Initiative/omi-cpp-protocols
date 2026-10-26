#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// For Symbol Update/Trading Status/System State refreshes this is the original sequence number from the live feed; for Order Book refresh this is the last sequence number on the live feed at the time of the refresh request.
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
