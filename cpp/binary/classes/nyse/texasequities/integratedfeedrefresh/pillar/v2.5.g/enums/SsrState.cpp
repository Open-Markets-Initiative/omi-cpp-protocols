#include "SsrState.hpp"

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(SsrState value) {
    switch (value) {
        case SsrState::NoShortSaleRestrictionInEffect: return "No Short Sale Restriction In Effect";
        case SsrState::ShortSaleRestrictionInEffect: return "Short Sale Restriction In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SsrState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
