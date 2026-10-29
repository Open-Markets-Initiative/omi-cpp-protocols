#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Previous order price.
struct PrevPrice {

    static constexpr const char* name = "Prev Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;

    // default constructor
    constexpr PrevPrice()
     : value{ 0 } {}

    // constructor for PrevPrice field
    constexpr explicit PrevPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PrevPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of PrevPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
