#include "AuctionType.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::Opening: return "Opening";
        case AuctionType::Reopening: return "Reopening";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
