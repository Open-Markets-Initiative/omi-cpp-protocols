#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// RFQ Price
struct WorkingPrice {

    static constexpr const char* name = "Working Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr WorkingPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit WorkingPrice(const std::int32_t value)
     : value{ value } {}

    // get value of WorkingPrice field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
