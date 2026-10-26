#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// Dirty Price
struct DirtyPrice {

    static constexpr const char* name = "Dirty Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr DirtyPrice()
     : value{ 0 } {}

    // constructor for DirtyPrice field
    constexpr explicit DirtyPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of DirtyPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of DirtyPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
