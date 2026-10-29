#include "SeriesType.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(SeriesType value) {
    switch (value) {
        case SeriesType::Standard: return "Standard";
        case SeriesType::Flex: return "Flex";
        case SeriesType::FlexPercentage: return "Flex Percentage";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SeriesType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
