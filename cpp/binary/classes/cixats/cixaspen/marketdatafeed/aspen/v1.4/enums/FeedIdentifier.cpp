#include "FeedIdentifier.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::string_view to_string(FeedIdentifier value) {
    switch (value) {
        case FeedIdentifier::Aspen: return "Aspen";
        case FeedIdentifier::AspenVert: return "Aspen Vert";
        case FeedIdentifier::Midpoint: return "Midpoint";
        case FeedIdentifier::AspenUat: return "Aspen Uat";
        case FeedIdentifier::AspenVertUat: return "Aspen Vert Uat";
        case FeedIdentifier::MidpointUat: return "Midpoint Uat";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FeedIdentifier value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
