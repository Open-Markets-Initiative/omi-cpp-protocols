#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Denotes a particular condition applicable to the quote.
struct QuoteCondition {

    static constexpr auto name = "Quote Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr QuoteCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuoteCondition(const char &value)
     : value{ value } {}

    // get value of QuoteCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
