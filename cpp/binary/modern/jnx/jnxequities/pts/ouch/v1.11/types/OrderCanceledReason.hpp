#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Reason order was reduced or canceled
struct OrderCanceledReason {

    static constexpr auto name = "Order Canceled Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderCanceledReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderCanceledReason(const char &value)
     : value{ value } {}

    // get value of OrderCanceledReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
