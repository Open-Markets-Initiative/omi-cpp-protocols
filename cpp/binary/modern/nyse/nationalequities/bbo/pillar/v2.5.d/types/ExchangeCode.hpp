#pragma once

#include <cstddef>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {


// For listed equity markets, the market where this symbol is listed.
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
