#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// minOrderQty
struct MinOrderQty {

    static constexpr const char* name = "Min Order Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;
static const type no_value = (-9223372036854775807LL - 1);

    // default constructor
    constexpr MinOrderQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MinOrderQty(const std::int64_t value)
     : value{ value } {}

    // get value of MinOrderQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
