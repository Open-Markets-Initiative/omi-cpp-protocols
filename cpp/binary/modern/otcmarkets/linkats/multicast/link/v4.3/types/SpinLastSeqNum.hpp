// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinLastSeqNum.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Last sequence number applied to this spin.
struct SpinLastSeqNum {

    static constexpr const char* name = "Spin Last Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SpinLastSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpinLastSeqNum(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SpinLastSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
