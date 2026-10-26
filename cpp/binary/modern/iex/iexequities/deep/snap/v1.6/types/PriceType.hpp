#pragma once

#include <cstddef>

namespace iex::iexequities::deep::snap::v1_6 {


// Price type identifier
struct PriceType {

    static constexpr auto name = "Price Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PriceType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceType(const char &value)
     : value{ value } {}

    // get value of PriceType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
