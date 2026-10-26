#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// Minimum quantity accepted for order entry. If tag 1093-LotType=4, this value is the minimum quantity for order entry expressed in the applicable units, specified in tag 996-UnitOfMeasure, e.g. megawatts
struct MinLotSize {

    static constexpr const char* name = "Min Lot Size";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr MinLotSize()
     : value{ 0 } {}

    // constructor for MinLotSize field
    constexpr explicit MinLotSize(const std::int32_t value)
     : value{ value } {}

    // get underlying integer of MinLotSize field
    [[nodiscard]] std::int32_t integer() const {
        return value;
    }

    // decimal value of MinLotSize field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int32_t value;
};
}
