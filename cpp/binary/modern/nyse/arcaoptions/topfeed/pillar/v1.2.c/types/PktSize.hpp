#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The size of the packet in bytes, including this 16 byte packet header
struct PktSize {

    static constexpr const char* name = "Pkt Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PktSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PktSize(const std::uint16_t value)
     : value{ value } {}

    // get value of PktSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
