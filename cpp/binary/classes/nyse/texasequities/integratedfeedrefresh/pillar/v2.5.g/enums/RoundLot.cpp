#include "RoundLot.hpp"

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(RoundLot value) {
    switch (value) {
        case RoundLot::Yes: return "Yes";
        case RoundLot::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RoundLot value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
