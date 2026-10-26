#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// This field contains the contract size for each instrument. Used in combination with tag 996-UnitofMeasure
struct UnitOfMeasureQty {

    static constexpr const char* name = "Unit Of Measure Qty";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor
    constexpr UnitOfMeasureQty()
     : value{ 0 } {}

    // constructor for UnitOfMeasureQty field
    constexpr explicit UnitOfMeasureQty(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UnitOfMeasureQty field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UnitOfMeasureQty field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
