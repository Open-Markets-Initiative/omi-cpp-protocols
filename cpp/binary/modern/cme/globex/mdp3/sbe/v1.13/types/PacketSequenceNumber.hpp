#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Packet Sequence Number
struct PacketSequenceNumber {

    static constexpr const char* name = "Packet Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PacketSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketSequenceNumber(const std::uint32_t value)
     : value{ value } {}

    // get value of PacketSequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
