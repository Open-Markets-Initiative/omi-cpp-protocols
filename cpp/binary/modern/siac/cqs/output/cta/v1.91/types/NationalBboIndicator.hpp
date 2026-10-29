#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Indicates the affect the new quote has on the National BBO.
struct NationalBboIndicator {

    static constexpr auto name = "National Bbo Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr NationalBboIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NationalBboIndicator(const char &value)
     : value{ value } {}

    // get value of NationalBboIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
