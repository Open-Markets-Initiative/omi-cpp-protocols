#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::cts::output::cta::v2_11_b {

// Contains the total number of shares traded for each Participant. Has implied 6 decimal places
struct FractionalTradeTotalVolume {

    static constexpr const char* name = "Fractional Trade Total Volume";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 6;
    static constexpr double denominator = 1000000;
    using type = std::uint64_t;

    // default constructor
    constexpr FractionalTradeTotalVolume()
     : value{ 0 } {}

    // constructor for FractionalTradeTotalVolume field
    constexpr explicit FractionalTradeTotalVolume(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of FractionalTradeTotalVolume field
    [[nodiscard]] std::uint64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of FractionalTradeTotalVolume field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::uint64_t value;
};
}
