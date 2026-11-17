// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/SpinMsgCt.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Total number of messages in the spin.
struct SpinMsgCt {

    static constexpr const char* name = "Spin Msg Ct";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SpinMsgCt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpinMsgCt(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SpinMsgCt field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
