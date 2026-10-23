#include "SignificantImbalance.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(SignificantImbalance value) {
    switch (value) {
        case SignificantImbalance::Default: return "Default";
        case SignificantImbalance::TheCurrentImbalanceIsSignificant: return "The Current Imbalance Is Significant";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SignificantImbalance value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
