#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// 
struct QuoteReqIdData {

    static constexpr auto name = "Quote Req Id Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr QuoteReqIdData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteReqIdData(const char &value)
     : value{ value } {}

    // get value of QuoteReqIdData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
