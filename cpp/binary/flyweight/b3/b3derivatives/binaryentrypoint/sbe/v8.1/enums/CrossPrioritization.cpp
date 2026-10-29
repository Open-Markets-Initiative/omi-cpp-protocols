#include "CrossPrioritization.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(CrossPrioritization value) {
    switch (value) {
        case CrossPrioritization::None: return "None";
        case CrossPrioritization::BuySideIsPrioritized: return "Buy Side Is Prioritized";
        case CrossPrioritization::SellSideIsPrioritized: return "Sell Side Is Prioritized";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossPrioritization value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
