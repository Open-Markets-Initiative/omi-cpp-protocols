#pragma once

#include <cstddef>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {


// For Auction Types=C or P in NYSE-listed symbols. Using historical closing data for each symbol,NYSE will set this indicator if the Continuous Book Clearing Price is more than a ‘significant’ range away from the Reference Price.
struct SignificantImbalance {

    static constexpr auto name = "Significant Imbalance";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SignificantImbalance()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SignificantImbalance(const char &value)
     : value{ value } {}

    // get value of SignificantImbalance field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
