#pragma once

#include <cstddef>

namespace jnx::jnxequities::pts::ouch::v1_11 {


// Reason the order was rejected
struct OrderRejectedReason {

    static constexpr auto name = "Order Rejected Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OrderRejectedReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderRejectedReason(const char &value)
     : value{ value } {}

    // get value of OrderRejectedReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
