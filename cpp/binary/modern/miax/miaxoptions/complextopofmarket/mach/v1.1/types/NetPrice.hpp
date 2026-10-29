#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// The net transaction price of the complex package. (Leg component prices times base sizes +/- other leg component prices times their base sizes, split pricing accounted for)
struct NetPrice {

    static constexpr const char* name = "Net Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 4;
    static constexpr double denominator = 10000;
    using type = std::int64_t;

    // default constructor
    constexpr NetPrice()
     : value{ 0 } {}

    // constructor for NetPrice field
    constexpr explicit NetPrice(const std::int64_t value)
     : value{ value } {}

    // get underlying integer of NetPrice field
    [[nodiscard]] std::int64_t integer() const {
        return value;
    }

    // decimal value of NetPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
