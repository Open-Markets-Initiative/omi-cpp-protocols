#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Indices message type
enum class IndicesMessageType : char {
    IndexMessage = 'I',            // Index Message
    BidAndOfferIndexMessage = 'Q', // Bid And Offer Index Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IndicesMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IndicesMessageType value);

} // namespace siac::cts::output::cta::v1_91
