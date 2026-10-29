#pragma once

#include <cstddef>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {


// Exchanges where it is listed
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
