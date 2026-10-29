#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// quoteStatusResponseTo
struct QuoteStatusResponseTo {

    static constexpr auto name = "Quote Status Response To";
    static constexpr std::size_t size = 1;
    using type = char;
static const type no_value = '0';

    // default constructor
    constexpr QuoteStatusResponseTo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteStatusResponseTo(const char &value)
     : value{ value } {}

    // get value of QuoteStatusResponseTo field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
