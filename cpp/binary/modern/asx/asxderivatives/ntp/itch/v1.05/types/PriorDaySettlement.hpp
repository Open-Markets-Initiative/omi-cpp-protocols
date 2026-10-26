#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Prior Day Settlement price. Divide by the Price Fractional Denominator to determine the floating point value.
struct PriorDaySettlement {

    static constexpr const char* name = "Prior Day Settlement";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr PriorDaySettlement()
     : value{ 0 } {}

    // constructor for PriorDaySettlement field
    constexpr explicit PriorDaySettlement(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of PriorDaySettlement field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of PriorDaySettlement field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
