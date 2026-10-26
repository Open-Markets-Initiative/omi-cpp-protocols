#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// AsOfSequenceNumber
struct AsOfSequenceNumber {

    static constexpr const char* name = "As Of Sequence Number";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr AsOfSequenceNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AsOfSequenceNumber(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of AsOfSequenceNumber field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
