#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates which Limit Up / Limit Down price band calculation parameter is to be used for the instrument
struct LuldReferencePriceTier {

    static constexpr auto name = "Luld Reference Price Tier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LuldReferencePriceTier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LuldReferencePriceTier(const char &value)
     : value{ value } {}

    // get value of LuldReferencePriceTier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
