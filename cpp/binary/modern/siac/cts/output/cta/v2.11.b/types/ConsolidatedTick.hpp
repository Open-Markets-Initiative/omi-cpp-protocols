#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Consolidated tick direction
struct ConsolidatedTick {

    static constexpr auto name = "Consolidated Tick";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ConsolidatedTick()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ConsolidatedTick(const char &value)
     : value{ value } {}

    // get value of ConsolidatedTick field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
