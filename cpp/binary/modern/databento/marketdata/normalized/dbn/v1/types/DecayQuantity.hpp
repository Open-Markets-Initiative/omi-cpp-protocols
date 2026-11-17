// Databento.MarketData.Normalized.Dbn.v1: types/DecayQuantity.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace databento::marketdata::normalized::dbn::v1 {

// The decay quantity
struct DecayQuantity {

    static constexpr const char* name = "Decay Quantity";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr DecayQuantity()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DecayQuantity(const std::int32_t value)
     : value{ value } {}

    // get value of DecayQuantity field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
