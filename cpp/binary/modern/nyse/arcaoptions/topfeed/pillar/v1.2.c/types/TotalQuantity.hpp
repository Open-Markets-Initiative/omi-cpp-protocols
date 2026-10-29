#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Total quantity
struct TotalQuantity {

    static constexpr const char* name = "Total Quantity";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalQuantity(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalQuantity field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
