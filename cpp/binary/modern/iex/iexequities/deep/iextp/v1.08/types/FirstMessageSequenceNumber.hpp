#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {

// Sequence of the first message in the segment
struct FirstMessageSequenceNumber {

    static constexpr const char* name = "First Message Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr FirstMessageSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstMessageSequenceNumber(const std::uint64_t value)
     : value{ value } {}

    // get value of FirstMessageSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
