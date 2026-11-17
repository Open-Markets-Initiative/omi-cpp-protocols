// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AssetClass.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Asset class indicator.
struct AssetClass {

    static constexpr auto name = "Asset Class";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AssetClass()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AssetClass(const std::uint8_t &value)
     : value{ value } {}

    // get value of AssetClass field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
