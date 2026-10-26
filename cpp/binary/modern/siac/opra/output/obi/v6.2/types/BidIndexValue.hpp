#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// The Bid Index Value represents the value of the index’s calculation formula using the current bid values of the component securities.
struct BidIndexValue {

    static constexpr const char* name = "Bid Index Value";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr BidIndexValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BidIndexValue(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of BidIndexValue field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
