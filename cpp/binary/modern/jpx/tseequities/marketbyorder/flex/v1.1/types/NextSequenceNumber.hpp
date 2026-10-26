#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// For retransmission set to 0; for snapshot indicates the next multicast transmission sequence number that should be received after capturing the snapshot
struct NextSequenceNumber {

    static constexpr const char* name = "Next Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr NextSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NextSequenceNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of NextSequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
