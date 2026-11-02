#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v3 {

// The min lot size round lot
struct MinLotSizeRoundLot {

    static constexpr const char* name = "Min Lot Size Round Lot";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr MinLotSizeRoundLot()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinLotSizeRoundLot(const std::int32_t value)
     : value{ value } {}

    // get value of MinLotSizeRoundLot field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
