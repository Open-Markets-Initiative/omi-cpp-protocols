#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The number of mapping intervals of the symbol
struct IntervalCount {

    static constexpr const char* name = "Interval Count";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr IntervalCount()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IntervalCount(const std::uint32_t value)
     : value{ value } {}

    // get value of IntervalCount field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
