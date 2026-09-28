#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// fillQty
struct FillQty {

    static constexpr const char* name = "Fill Qty";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr FillQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FillQty(const std::int64_t value)
     : value{ value } {}

    // get value of FillQty field
    [[nodiscard]] std::int64_t get() const {
        return value;
    }

  protected:
    std::int64_t value;
};
}
