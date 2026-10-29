#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Explicit strike price of the option. Refer to data types for field processing notes
struct StrikePrice {

    static constexpr const char* name = "Strike Price";
    static constexpr std::size_t size =  4;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::uint32_t;

    // default constructor
    constexpr StrikePrice()
     : value{ 0 } {}

    // constructor for StrikePrice field
    constexpr explicit StrikePrice(const std::uint32_t value)
     : value{ value } {}

    // get underlying integer of StrikePrice field
    [[nodiscard]] std::uint32_t integer() const {
        return value;
    }

    // decimal value of StrikePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint32_t value;
};
}
