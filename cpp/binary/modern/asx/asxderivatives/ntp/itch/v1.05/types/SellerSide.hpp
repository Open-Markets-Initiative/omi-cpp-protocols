#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Type of order
struct SellerSide {

    static constexpr auto name = "Seller Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SellerSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SellerSide(const char &value)
     : value{ value } {}

    // get value of SellerSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
