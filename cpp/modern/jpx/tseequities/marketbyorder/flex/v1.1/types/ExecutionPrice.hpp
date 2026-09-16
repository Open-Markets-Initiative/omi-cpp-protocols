#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Execution price
struct ExecutionPrice {

    static constexpr const char* name = "Execution Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr ExecutionPrice()
     : value{ 0 } {}

    // constructor for ExecutionPrice field
    constexpr explicit ExecutionPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of ExecutionPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of ExecutionPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
