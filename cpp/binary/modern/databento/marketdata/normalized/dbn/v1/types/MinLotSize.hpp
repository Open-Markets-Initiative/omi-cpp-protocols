#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The min lot size
struct MinLotSize {

    static constexpr const char* name = "Min Lot Size";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinLotSize(const std::int32_t value)
     : value{ value } {}

    // get value of MinLotSize field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
