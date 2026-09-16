#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates if the market participant firm qualifies as a Primary Market Maker in accordance with NASDAQ marketplace rules
struct PrimaryMarketMaker {

    static constexpr auto name = "Primary Market Maker";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr PrimaryMarketMaker()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrimaryMarketMaker(const char &value)
     : value{ value } {}

    // get value of PrimaryMarketMaker field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
