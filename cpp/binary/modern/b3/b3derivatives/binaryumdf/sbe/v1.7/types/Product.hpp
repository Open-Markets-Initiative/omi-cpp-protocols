#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// product
struct Product {

    static constexpr auto name = "Product";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Product()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Product(const std::uint8_t &value)
     : value{ value } {}

    // get value of Product field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
