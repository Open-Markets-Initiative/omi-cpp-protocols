#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// The message sequence number of the first message in this packet
struct SeqNum {

    static constexpr const char* name = "Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of SeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
