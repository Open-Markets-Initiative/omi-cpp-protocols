#pragma once

#include <cstddef>
#include <cstdint>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Quantity canceled - Quantity 6 implied decimals
struct QuantityCanceled {

    static constexpr const char* name = "Quantity Canceled";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr QuantityCanceled()
     : value{ 0 } {}

    // constructor for QuantityCanceled field
    constexpr explicit QuantityCanceled(const std::uint64_t value)
     : value{ value } {}

    // get underlying integer of QuantityCanceled field
    [[nodiscard]] std::uint64_t integer() const {
        return value;
    }

    // decimal value of QuantityCanceled field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
