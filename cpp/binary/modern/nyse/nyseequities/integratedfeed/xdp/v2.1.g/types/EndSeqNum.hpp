#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// The end sequence number of the range of messages to be retransmitted.
struct EndSeqNum {

    static constexpr const char* name = "End Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr EndSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EndSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of EndSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
