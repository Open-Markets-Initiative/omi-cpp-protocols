#pragma once

#include <cstddef>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {


// The allocation model used by the MIAX Futures Onyx Trading Platform for the Product
struct MatchAlgorithm {

    static constexpr auto name = "Match Algorithm";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MatchAlgorithm()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchAlgorithm(const char &value)
     : value{ value } {}

    // get value of MatchAlgorithm field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
