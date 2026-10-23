#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v8 {


// Order book update action to be applied to the order referenced by OrderID
struct OrderUpdateAction {

    static constexpr auto name = "Order Update Action";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr OrderUpdateAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderUpdateAction(const std::uint8_t &value)
     : value{ value } {}

    // get value of OrderUpdateAction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
