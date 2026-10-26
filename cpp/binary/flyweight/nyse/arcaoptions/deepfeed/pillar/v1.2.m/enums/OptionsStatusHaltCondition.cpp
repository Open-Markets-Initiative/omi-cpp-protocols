#include "OptionsStatusHaltCondition.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(OptionsStatusHaltCondition value) {
    switch (value) {
        case OptionsStatusHaltCondition::SeriesNotDelayedhalted: return "Series Not Delayedhalted";
        case OptionsStatusHaltCondition::OptionSeriesIsHalted: return "Option Series Is Halted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptionsStatusHaltCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
