#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The current reference price when the DLCR volatility test has successfully passed
struct NearExecutionPrice {

    static constexpr const char* name = "Near Execution Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr NearExecutionPrice()
     : value{ 0 } {}

    // constructor for NearExecutionPrice field
    constexpr explicit NearExecutionPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NearExecutionPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NearExecutionPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
