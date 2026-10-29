#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The unique ID of this message in the sequence of messages published for this specific series
struct SeriesSeqNum {

    static constexpr const char* name = "Series Seq Num";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SeriesSeqNum()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeriesSeqNum(const std::uint32_t value)
     : value{ value } {}

    // get value of SeriesSeqNum field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
