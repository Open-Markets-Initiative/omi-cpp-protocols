// Cme.Globex.Mdp3.Sbe.v1.9: types/UnitOfMeasureQtyEx.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {

// This field contains the contract size for each instrument. Used in combination with tag 996-UnitofMeasure
struct UnitOfMeasureQtyEx {

    static constexpr const char* name = "Unit Of Measure Qty Ex";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;
static const type no_value = 9223372036854775807;

    // default constructor: the null the model states, where it states one
    constexpr UnitOfMeasureQtyEx()
     : value{ no_value } {}

    // constructor for UnitOfMeasureQtyEx field
    constexpr explicit UnitOfMeasureQtyEx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UnitOfMeasureQtyEx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UnitOfMeasureQtyEx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
