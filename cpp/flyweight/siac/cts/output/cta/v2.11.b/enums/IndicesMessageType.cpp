#include "IndicesMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(IndicesMessageType value) {
    switch (value) {
        case IndicesMessageType::Indices: return "Indices";
        case IndicesMessageType::BidAndOfferIndex: return "Bid And Offer Index";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IndicesMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
