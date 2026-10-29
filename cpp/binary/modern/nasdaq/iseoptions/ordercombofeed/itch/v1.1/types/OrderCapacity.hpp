#pragma once

#include <cstddef>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {


// Order Capacity value
struct OrderCapacity {

    static constexpr auto name = "Order Capacity";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderCapacity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderCapacity(const char &value)
     : value{ value } {}

    // get value of OrderCapacity field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
