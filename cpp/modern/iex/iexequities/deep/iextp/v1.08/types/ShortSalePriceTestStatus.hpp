#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deep::iextp::v1_08 {


// Reg. SHO short sale price test restriction status
struct ShortSalePriceTestStatus {

    static constexpr auto name = "Short Sale Price Test Status";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ShortSalePriceTestStatus()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSalePriceTestStatus(const std::uint8_t &value)
     : value{ value } {}

    // get value of ShortSalePriceTestStatus field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
