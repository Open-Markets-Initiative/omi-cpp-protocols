#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// For retransmission set to the first sequence number for the request; for snapshot set to 0
struct SequenceNumber {

    static constexpr const char* name = "Sequence Number";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SequenceNumber(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get value of SequenceNumber field
    [[nodiscard]] std::uint32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint32_t value;
};
}
