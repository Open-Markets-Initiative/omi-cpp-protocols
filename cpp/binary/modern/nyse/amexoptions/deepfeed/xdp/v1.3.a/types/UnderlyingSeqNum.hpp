#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Sequence number of messages for the underlying symbol.
struct UnderlyingSeqNum {

    static constexpr const char* name = "Underlying Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UnderlyingSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of UnderlyingSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
