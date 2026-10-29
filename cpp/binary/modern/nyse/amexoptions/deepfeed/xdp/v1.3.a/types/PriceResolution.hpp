#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {


// Price Resolution value
struct PriceResolution {

    static constexpr auto name = "Price Resolution";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PriceResolution()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PriceResolution(const std::uint8_t &value)
     : value{ value } {}

    // get value of PriceResolution field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
