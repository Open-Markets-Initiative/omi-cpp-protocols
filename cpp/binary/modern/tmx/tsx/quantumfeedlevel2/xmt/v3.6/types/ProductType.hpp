// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/ProductType.hpp
#pragma once

#include <cstddef>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {


// The Product Type For A Symbol
struct ProductType {

    static constexpr auto name = "Product Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ProductType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ProductType(const char &value)
     : value{ value } {}

    // get value of ProductType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
