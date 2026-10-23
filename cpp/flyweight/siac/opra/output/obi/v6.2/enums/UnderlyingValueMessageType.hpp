#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Underlying Value Message type
enum class UnderlyingValueMessageType : char {
    IndexBasedOnLastSale = ' ',    // Index Based On Last Sale
    IndexBasedOnBidAndOffer = 'I', // Index Based On Bid And Offer
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnderlyingValueMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnderlyingValueMessageType value);

} // namespace siac::opra::output::obi::v6_2
