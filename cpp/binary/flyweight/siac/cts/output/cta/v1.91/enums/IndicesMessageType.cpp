#include "IndicesMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(IndicesMessageType value) {
    switch (value) {
        case IndicesMessageType::IndexMessage: return "Index Message";
        case IndicesMessageType::BidAndOfferIndexMessage: return "Bid And Offer Index Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IndicesMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
