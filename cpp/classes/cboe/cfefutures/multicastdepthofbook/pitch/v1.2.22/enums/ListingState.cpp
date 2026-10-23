#include "ListingState.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::string_view to_string(ListingState value) {
    switch (value) {
        case ListingState::Active: return "Active";
        case ListingState::Inactive: return "Inactive";
        case ListingState::Test: return "Test";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ListingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
