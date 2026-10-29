#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// This field qualifies an instrument type on BSE.
struct ProductComplex {

    static constexpr auto name = "Product Complex";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ProductComplex()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProductComplex(const std::uint8_t &value)
     : value{ value } {}

    // get value of ProductComplex field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
