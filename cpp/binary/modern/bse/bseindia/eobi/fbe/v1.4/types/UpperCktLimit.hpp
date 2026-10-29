#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Upper Circuit Limit Price
struct UpperCktLimit {

    static constexpr const char* name = "Upper Ckt Limit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;

    // default constructor
    constexpr UpperCktLimit()
     : value{ 0 } {}

    // constructor for UpperCktLimit field
    constexpr explicit UpperCktLimit(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of UpperCktLimit field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of UpperCktLimit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
