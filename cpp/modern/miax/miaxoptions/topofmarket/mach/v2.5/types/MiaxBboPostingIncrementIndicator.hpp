#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// This is the Minimum Price Variation as agreed to by the Options industry (penny pilot program) and as published by MIAX
struct MiaxBboPostingIncrementIndicator {

    static constexpr auto name = "Miax Bbo Posting Increment Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MiaxBboPostingIncrementIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MiaxBboPostingIncrementIndicator(const char &value)
     : value{ value } {}

    // get value of MiaxBboPostingIncrementIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
