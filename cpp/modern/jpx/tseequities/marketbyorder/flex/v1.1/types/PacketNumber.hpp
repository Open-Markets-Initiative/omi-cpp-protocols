#pragma once

#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Packet number within a multi packet split set always 0 in arrowhead4 0
struct PacketNumber {

    static constexpr auto name = "Packet Number";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PacketNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PacketNumber(const std::uint8_t &value)
     : value{ value } {}

    // get value of PacketNumber field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
