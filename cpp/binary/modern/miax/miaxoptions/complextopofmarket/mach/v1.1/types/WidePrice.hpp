#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// MIAX Best price at the time stated in Timestamp and side specified in Message Type.
struct WidePrice {

    static constexpr const char* name = "Wide Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr WidePrice()
     : value{ 0 } {}

    // constructor for WidePrice field
    constexpr explicit WidePrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of WidePrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of WidePrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
