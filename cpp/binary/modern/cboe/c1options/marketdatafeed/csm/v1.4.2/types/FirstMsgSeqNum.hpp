// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/FirstMsgSeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The sequence number on the first message in this packet
struct FirstMsgSeqNum {

    static constexpr const char* name = "First Msg Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr FirstMsgSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FirstMsgSeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of FirstMsgSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
