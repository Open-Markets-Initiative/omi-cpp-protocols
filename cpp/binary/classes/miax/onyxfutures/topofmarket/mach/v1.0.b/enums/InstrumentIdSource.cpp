#include "InstrumentIdSource.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(InstrumentIdSource value) {
    switch (value) {
        case InstrumentIdSource::Exchange: return "Exchange";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrumentIdSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
