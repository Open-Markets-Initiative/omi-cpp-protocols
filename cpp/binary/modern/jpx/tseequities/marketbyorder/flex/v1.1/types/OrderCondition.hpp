#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates the order condition
struct OrderCondition {

    static constexpr auto name = "Order Condition";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr OrderCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderCondition(const std::uint8_t &value)
     : value{ value } {}

    // get value of OrderCondition field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
