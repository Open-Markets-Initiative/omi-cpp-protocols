#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// orderQty
struct OrderQty {

    static constexpr const char* name = "Order Qty";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr OrderQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderQty(const std::uint64_t value)
     : value{ value } {}

    // get value of OrderQty field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
