#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Last price at the time the execution was processed
struct LastPrice {

    static constexpr const char* name = "Last Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint64_t;

    // default constructor
    constexpr LastPrice()
     : value{ 0 } {}

    // constructor for LastPrice field
    constexpr explicit LastPrice(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LastPrice field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LastPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
