#include "ListingMarket.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::string_view to_string(ListingMarket value) {
    switch (value) {
        case ListingMarket::Tsx: return "Tsx";
        case ListingMarket::Venture: return "Venture";
        case ListingMarket::Cse: return "Cse";
        case ListingMarket::Neo: return "Neo";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ListingMarket value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
