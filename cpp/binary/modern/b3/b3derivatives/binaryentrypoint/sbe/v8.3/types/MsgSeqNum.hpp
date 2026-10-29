#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// msgSeqNum
struct MsgSeqNum {

    static constexpr const char* name = "Msg Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr MsgSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MsgSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of MsgSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
