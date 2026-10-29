#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Best price at the time stated in Timestamp and side specified in Message Type.
struct CompactPrice {

    static constexpr const char* name = "Compact Price";
    static constexpr std::size_t size =  2;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int16_t;

    // default constructor
    constexpr CompactPrice()
     : value{ 0 } {}

    // constructor for CompactPrice field
    constexpr explicit CompactPrice(const std::int16_t value)
     : value{ value } {}

    // get underlying integer of CompactPrice field
    [[nodiscard]] std::int16_t integer() const {
        return value;
    }

    // decimal value of CompactPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int16_t value;
};
}
