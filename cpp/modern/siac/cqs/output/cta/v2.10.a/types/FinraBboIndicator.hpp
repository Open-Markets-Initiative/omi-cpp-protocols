#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// For FINRA ADF, represents the FINRA BBO state of the FINRA ADF quote
struct FinraBboIndicator {

    static constexpr auto name = "Finra Bbo Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr FinraBboIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FinraBboIndicator(const char &value)
     : value{ value } {}

    // get value of FinraBboIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
