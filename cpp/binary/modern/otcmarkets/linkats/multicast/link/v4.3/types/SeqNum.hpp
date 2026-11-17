// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Channel specific Sequence number of packet
struct SeqNum {

    static constexpr const char* name = "Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
