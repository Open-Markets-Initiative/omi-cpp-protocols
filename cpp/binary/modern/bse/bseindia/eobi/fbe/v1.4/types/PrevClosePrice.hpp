#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Previous Close Price
struct PrevClosePrice {

    static constexpr const char* name = "Prev Close Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;

    // default constructor
    constexpr PrevClosePrice()
     : value{ 0 } {}

    // constructor for PrevClosePrice field
    constexpr explicit PrevClosePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of PrevClosePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of PrevClosePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
