#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Identifies series type
struct SeriesType {

    static constexpr auto name = "Series Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SeriesType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SeriesType(const std::uint8_t &value)
     : value{ value } {}

    // get value of SeriesType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
