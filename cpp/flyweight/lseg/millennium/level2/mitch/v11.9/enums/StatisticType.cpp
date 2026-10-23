#include "StatisticType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(StatisticType value) {
    switch (value) {
        case StatisticType::OpeningPrice: return "Opening Price";
        case StatisticType::ClosingPrice: return "Closing Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StatisticType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
