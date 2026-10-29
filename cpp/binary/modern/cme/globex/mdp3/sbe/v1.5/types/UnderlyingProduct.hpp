#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v5 {


// Product complex
struct UnderlyingProduct {

    static constexpr auto name = "Underlying Product";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr UnderlyingProduct()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingProduct(const std::uint8_t &value)
     : value{ value } {}

    // get value of UnderlyingProduct field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
