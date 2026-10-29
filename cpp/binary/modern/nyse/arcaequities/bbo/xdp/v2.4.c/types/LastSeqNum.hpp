#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// The last sequence number sent on the channel for any symbol. The refresh is the state of the order book as of this sequence number.
struct LastSeqNum {

    static constexpr const char* name = "Last Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of LastSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
