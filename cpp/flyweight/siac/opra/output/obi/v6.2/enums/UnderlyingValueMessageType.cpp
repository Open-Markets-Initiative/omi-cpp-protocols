#include "UnderlyingValueMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(UnderlyingValueMessageType value) {
    switch (value) {
        case UnderlyingValueMessageType::IndexBasedOnLastSale: return "Index Based On Last Sale";
        case UnderlyingValueMessageType::IndexBasedOnBidAndOffer: return "Index Based On Bid And Offer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnderlyingValueMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
