#include "MatchAlgorithm.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(MatchAlgorithm value) {
    switch (value) {
        case MatchAlgorithm::PriceThenTime: return "Price Then Time";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MatchAlgorithm value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
