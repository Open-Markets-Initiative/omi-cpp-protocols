#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Reports trading suspensions, price indications, trading range indications, LULD Price Bands and Market Wide Circuit Breaker activity
struct SecurityStatusIndicator {

    static constexpr auto name = "Security Status Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityStatusIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityStatusIndicator(const char &value)
     : value{ value } {}

    // get value of SecurityStatusIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
