// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/PriceVariation.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// This Field Indicates The Absolute Value Of The Percentage Of Deviation Of The Near Indicative Closing Price From The Reference Price
struct PriceVariation {

    static constexpr const char* name = "Price Variation";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr PriceVariation()
     : value{ no_value } {}

    // constructor for PriceVariation field
    constexpr explicit PriceVariation(const std::uint32_t value)
     : value{ value } {}

    // get underlying integer of PriceVariation field
    [[nodiscard]] std::uint32_t integer() const {
        return value;
    }

    // does PriceVariation hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of PriceVariation field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
