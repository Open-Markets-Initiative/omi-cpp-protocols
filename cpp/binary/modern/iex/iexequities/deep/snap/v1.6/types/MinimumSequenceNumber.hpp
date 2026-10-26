#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::snap::v1_6 {

// Minimum sequence number useable by the client, zero returns the latest snapshot available
struct MinimumSequenceNumber {

    static constexpr const char* name = "Minimum Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr MinimumSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinimumSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of MinimumSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
