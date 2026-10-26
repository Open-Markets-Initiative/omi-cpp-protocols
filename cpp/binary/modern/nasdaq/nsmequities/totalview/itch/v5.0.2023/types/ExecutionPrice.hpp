#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The price at which the order execution occurred
struct ExecutionPrice {

    static constexpr const char* name = "Execution Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr ExecutionPrice()
     : value{ 0 } {}

    // constructor for ExecutionPrice field
    constexpr explicit ExecutionPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ExecutionPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ExecutionPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
