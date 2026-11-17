// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: types/MaxOrderQty.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// maxOrderQty
struct MaxOrderQty {

    static constexpr const char* name = "Max Order Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor: the null the model states, where it states one
    constexpr MaxOrderQty()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit MaxOrderQty(const std::int64_t value)
     : value{ value } {}

    // get value of MaxOrderQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
