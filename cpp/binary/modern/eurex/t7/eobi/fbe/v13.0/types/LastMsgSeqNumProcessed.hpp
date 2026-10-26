#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {

// 
struct LastMsgSeqNumProcessed {

    static constexpr const char* name = "Last Msg Seq Num Processed";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0xFFFFFFFF;
static const type maximum_value = 4294967294;
static const type minimum_value = 0;

    // default constructor
    constexpr LastMsgSeqNumProcessed()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastMsgSeqNumProcessed(const std::uint32_t value)
     : value{ value } {}

    // get value of LastMsgSeqNumProcessed field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
