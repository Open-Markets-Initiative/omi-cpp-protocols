#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::tops::iextp::v1_66 {

// Trade price
struct Price {

    static constexpr const char* name = "Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr Price()
     : value{ 0 } {}

    // constructor for Price field
    constexpr explicit Price(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of Price field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of Price field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
