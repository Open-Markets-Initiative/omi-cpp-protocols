#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::itch::v1_6 {


// Type of the order.
struct OrderType {

    static constexpr auto name = "Order Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderType(const char &value)
     : value{ value } {}

    // get value of OrderType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
