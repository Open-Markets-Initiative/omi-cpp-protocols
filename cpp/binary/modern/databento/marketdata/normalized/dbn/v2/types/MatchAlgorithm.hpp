// Databento.MarketData.Normalized.Dbn.v2: types/MatchAlgorithm.hpp
#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v2 {


// The matching algorithm used for the instrument, typically FIFO
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
