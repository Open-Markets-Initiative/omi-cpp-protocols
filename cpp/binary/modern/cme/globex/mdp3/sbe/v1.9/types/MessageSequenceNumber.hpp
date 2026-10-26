#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// Packet Sequence Number
struct MessageSequenceNumber {

    static constexpr const char* name = "Message Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MessageSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageSequenceNumber(const std::uint32_t value)
     : value{ value } {}

    // get value of MessageSequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
