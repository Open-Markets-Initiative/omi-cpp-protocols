#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Will be provided for updates as a result of any changes to the prices or sizes of the MBBO for an Simple Instrument or a Complex Instrument
struct MbbPrice {

    static constexpr const char* name = "Mbb Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 9;
    static constexpr double denominator = 1000000000;
    using type = std::int64_t;

    // default constructor
    constexpr MbbPrice()
     : value{ 0 } {}

    // constructor for MbbPrice field
    constexpr explicit MbbPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of MbbPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of MbbPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
