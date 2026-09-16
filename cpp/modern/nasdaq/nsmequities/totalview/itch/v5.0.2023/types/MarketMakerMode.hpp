#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the quoting participant's registration status in relation to SEC Rules 101 and 104 of Regulation M
struct MarketMakerMode {

    static constexpr auto name = "Market Maker Mode";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketMakerMode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketMakerMode(const char &value)
     : value{ value } {}

    // get value of MarketMakerMode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
