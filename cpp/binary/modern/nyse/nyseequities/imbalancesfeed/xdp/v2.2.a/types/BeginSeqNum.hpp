#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// The beginning sequence number of the range of messages to be retransmitted.
struct BeginSeqNum {

    static constexpr const char* name = "Begin Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr BeginSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BeginSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of BeginSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
