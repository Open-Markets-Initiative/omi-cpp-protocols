#include "CrossType.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::NasdaqOpeningReopening: return "Nasdaq Opening Reopening";
        case CrossType::PriceImprovement: return "Price Improvement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
