#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {


// For listed equity markets, the market where this symbol is listed
struct ExchangeCode {

    static constexpr auto name = "Exchange Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExchangeCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExchangeCode(const char &value)
     : value{ value } {}

    // get value of ExchangeCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
