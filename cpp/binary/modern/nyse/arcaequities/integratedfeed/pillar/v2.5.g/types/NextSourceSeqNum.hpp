#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// The sequence number in the next message for this symbol.
struct NextSourceSeqNum {

    static constexpr const char* name = "Next Source Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NextSourceSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NextSourceSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of NextSourceSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
