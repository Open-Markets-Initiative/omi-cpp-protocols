// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: types/ApplSeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Sequence number for Refresh message, will be set per line and reset to 1 (one) when refresh is completed
struct ApplSeqNum {

    static constexpr const char* name = "Appl Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ApplSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ApplSeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of ApplSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
