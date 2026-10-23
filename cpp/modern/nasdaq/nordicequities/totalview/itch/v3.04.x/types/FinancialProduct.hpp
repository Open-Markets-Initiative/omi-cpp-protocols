#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Type of financial product
struct FinancialProduct {

    static constexpr auto name = "Financial Product";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr FinancialProduct()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinancialProduct(const std::uint8_t &value)
     : value{ value } {}

    // get value of FinancialProduct field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
