#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v1_91 {

// The Dollar Value represents the total dollar worth of the daily trade transactions.
struct DollarValue {

    static constexpr const char* name = "Dollar Value";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr DollarValue()
     : value{ 0 } {}

    // constructor for DollarValue field
    constexpr explicit DollarValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of DollarValue field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of DollarValue field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
