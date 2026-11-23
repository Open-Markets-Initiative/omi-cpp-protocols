// Eurex.T7.Eobi.Fbe.v15.0: types/BidPx.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct BidPx {

    static constexpr const char* name = "Bid Px";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;
static const type no_value = 0x8000000000000000;
static const type maximum_value = 92233720368.54775807;
static const type minimum_value = -92233720368.54775807;

    // default constructor: the null the model states, where it states one
    constexpr BidPx()
     : value{ no_value } {}

    // constructor for BidPx field
    constexpr explicit BidPx(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of BidPx field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // does BidPx hold a value, rather than the one reserved for none
    [[nodiscard]] bool has_value() const {
        return integer() != no_value;
    }

    // decimal value of BidPx field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
