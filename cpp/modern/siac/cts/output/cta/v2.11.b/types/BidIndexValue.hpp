#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Represents the value of the index's calculation formula using the current Bid values of the component securities. Has implied 6 decimal places
struct BidIndexValue {

    static constexpr const char* name = "Bid Index Value";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr BidIndexValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidIndexValue(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidIndexValue field
    [[nodiscard]] std::int64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int64_t value;
};
}
