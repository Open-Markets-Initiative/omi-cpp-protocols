#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Multiplier to calculate quantity in measurement units
struct MultiplierForCalculatingQuantityInMeasurementUnit {

    static constexpr const char* name = "Multiplier For Calculating Quantity In Measurement Unit";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr MultiplierForCalculatingQuantityInMeasurementUnit()
     : value{ 0 } {}

    // constructor for MultiplierForCalculatingQuantityInMeasurementUnit field
    constexpr explicit MultiplierForCalculatingQuantityInMeasurementUnit(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of MultiplierForCalculatingQuantityInMeasurementUnit field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of MultiplierForCalculatingQuantityInMeasurementUnit field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
