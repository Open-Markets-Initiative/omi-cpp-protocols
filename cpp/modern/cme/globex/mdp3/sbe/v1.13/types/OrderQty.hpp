#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Quantity requested
struct OrderQty {

    static constexpr const char* name = "Order Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr OrderQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderQty(const std::int32_t value)
     : value{ value } {}

    // get value of OrderQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
