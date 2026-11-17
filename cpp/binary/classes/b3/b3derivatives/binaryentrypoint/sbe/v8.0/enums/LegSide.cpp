// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.0: enums/LegSide.cpp
#include "LegSide.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Buy: return "Buy";
        case LegSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
