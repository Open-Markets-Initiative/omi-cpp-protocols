#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies the type of Quote message
struct QuoteMessageType {

    static constexpr auto name = "Quote Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr QuoteMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteMessageType(const char &value)
     : value{ value } {}

    // get value of QuoteMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
