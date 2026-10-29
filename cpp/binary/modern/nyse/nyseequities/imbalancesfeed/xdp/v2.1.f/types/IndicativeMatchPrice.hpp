#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// For Pillar-powered markets, the price that has the highest executable volume of auction-eligible shares, subject to auction collars.
struct IndicativeMatchPrice {

    static constexpr const char* name = "Indicative Match Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr IndicativeMatchPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndicativeMatchPrice(const std::uint32_t value)
     : value{ value } {}

    // get value of IndicativeMatchPrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
