#include "Opening.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(Opening value) {
    switch (value) {
        case Opening::None: return "None";
        case Opening::MarketCenterOpeningTrade: return "Market Center Opening Trade";
        case Opening::ReopeningTrade: return "Reopening Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Opening value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
