#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {

// In Book entry - aggregate number of orders at given price level
struct NumberOfOrders {

    static constexpr const char* name = "Number Of Orders";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr NumberOfOrders()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfOrders(const std::int32_t value)
     : value{ value } {}

    // get value of NumberOfOrders field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
