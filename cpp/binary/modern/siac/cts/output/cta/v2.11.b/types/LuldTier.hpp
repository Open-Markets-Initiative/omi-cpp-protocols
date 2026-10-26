#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the Limit Up Limit Down tier of the security symbol
struct LuldTier {

    static constexpr auto name = "Luld Tier";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr LuldTier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LuldTier(const char &value)
     : value{ value } {}

    // get value of LuldTier field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
