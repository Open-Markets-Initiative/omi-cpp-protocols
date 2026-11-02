#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The min lot size block
struct MinLotSizeBlock {

    static constexpr const char* name = "Min Lot Size Block";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinLotSizeBlock()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinLotSizeBlock(const std::int32_t value)
     : value{ value } {}

    // get value of MinLotSizeBlock field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
