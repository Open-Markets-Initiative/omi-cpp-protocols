#pragma once

#include <cstddef>

namespace cme::mdp3::v13 {


// Matching algorithm
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
