#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {

// Per-packet sequence number; 0xFFFFFFFF for unsequenced packets (heartbeats)
struct MsgSeqNum {

    static constexpr const char* name = "Msg Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0xFFFFFFFF;
static const type maximum_value = 4294967294;
static const type minimum_value = 0;

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
