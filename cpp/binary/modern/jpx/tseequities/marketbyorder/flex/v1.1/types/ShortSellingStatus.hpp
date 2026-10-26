#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates application of the Short Selling Regulation
struct ShortSellingStatus {

    static constexpr auto name = "Short Selling Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ShortSellingStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSellingStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of ShortSellingStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
