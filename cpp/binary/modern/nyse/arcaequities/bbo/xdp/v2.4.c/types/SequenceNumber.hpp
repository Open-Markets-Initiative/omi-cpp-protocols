#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// The message sequence number of the first message in this packet
struct SequenceNumber {

    static constexpr const char* name = "Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequenceNumber(const std::uint32_t value)
     : value{ value } {}

    // get value of SequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
