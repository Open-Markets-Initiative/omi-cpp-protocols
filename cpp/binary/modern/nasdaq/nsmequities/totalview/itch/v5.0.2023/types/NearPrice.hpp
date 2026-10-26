#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// A hypothetical auction-clearing price for cross orders as well as continuous orders
struct NearPrice {

    static constexpr const char* name = "Near Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr NearPrice()
     : value{ 0 } {}

    // constructor for NearPrice field
    constexpr explicit NearPrice(const std::uint32_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of NearPrice field
    [[nodiscard]] std::uint32_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of NearPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
