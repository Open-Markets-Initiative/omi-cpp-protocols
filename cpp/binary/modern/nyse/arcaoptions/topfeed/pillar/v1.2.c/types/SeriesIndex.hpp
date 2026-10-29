#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The unique ID of this series for all products within this market
struct SeriesIndex {

    static constexpr const char* name = "Series Index";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SeriesIndex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeriesIndex(const std::uint32_t value)
     : value{ value } {}

    // get value of SeriesIndex field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
