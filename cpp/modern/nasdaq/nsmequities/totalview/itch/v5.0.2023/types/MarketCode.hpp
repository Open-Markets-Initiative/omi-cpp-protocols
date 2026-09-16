#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Market Code
struct MarketCode {

    static constexpr auto name = "Market Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketCode(const char &value)
     : value{ value } {}

    // get value of MarketCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
