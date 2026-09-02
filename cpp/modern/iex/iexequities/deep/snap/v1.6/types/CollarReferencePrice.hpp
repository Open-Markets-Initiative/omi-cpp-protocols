#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::snap::v1_6 {

// Reference priced used for the auction collar, if any
struct CollarReferencePrice {

    static constexpr const char* name = "Collar Reference Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr CollarReferencePrice()
     : value{ 0 } {}

    // constructor for CollarReferencePrice field
    constexpr explicit CollarReferencePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of CollarReferencePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of CollarReferencePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
