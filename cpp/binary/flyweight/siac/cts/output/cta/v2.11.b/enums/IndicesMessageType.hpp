#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Index message
enum class IndicesMessageType : char {
    Indices = 'I',          // Indices
    BidAndOfferIndex = 'Q', // Bid And Offer Index
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IndicesMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IndicesMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
