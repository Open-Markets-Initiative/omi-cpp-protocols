#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// refSeqNum
struct RefSeqNum {

    static constexpr const char* name = "Ref Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RefSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RefSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of RefSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
