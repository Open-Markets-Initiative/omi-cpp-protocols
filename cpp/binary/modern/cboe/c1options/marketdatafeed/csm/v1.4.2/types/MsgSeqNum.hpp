// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/MsgSeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Message Sequence Number
struct MsgSeqNum {

    static constexpr const char* name = "Msg Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MsgSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MsgSeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of MsgSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
