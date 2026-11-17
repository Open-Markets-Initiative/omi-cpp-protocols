// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ChannelSeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Monotonically increasing message sequence number at the channel level.
struct ChannelSeqNum {

    static constexpr const char* name = "Channel Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ChannelSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ChannelSeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ChannelSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
