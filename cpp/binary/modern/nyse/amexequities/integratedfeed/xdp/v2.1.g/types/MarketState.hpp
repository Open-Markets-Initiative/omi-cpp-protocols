#pragma once

#include <cstddef>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {


// The current Market State, which this msg updates if the Security Status field contains a Market State Code.
struct MarketState {

    static constexpr auto name = "Market State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MarketState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketState(const char &value)
     : value{ value } {}

    // get value of MarketState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
