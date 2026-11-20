// Nyse.NyseEquities.ImbalancesFeed.Xdp.v2.2.a: enums/SignificantImbalance.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// For Auction Types=C or P in NYSE-listed symbols. Using historical closing data for each
// symbol,NYSE will set this indicator if the Continuous Book Clearing Price is more than a
// ‘significant’ range away from the Reference Price.
enum class SignificantImbalance : char {
    NotSignificant = ' ', // Not Significant
    Significant = 'Y',    // Significant
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SignificantImbalance value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SignificantImbalance value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
