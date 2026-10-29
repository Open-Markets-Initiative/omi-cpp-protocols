#include "InstrumentType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(InstrumentType value) {
    switch (value) {
        case InstrumentType::Futures: return "Futures";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrumentType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
