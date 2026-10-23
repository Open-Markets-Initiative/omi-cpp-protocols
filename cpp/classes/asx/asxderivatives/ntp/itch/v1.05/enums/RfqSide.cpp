#include "RfqSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(RfqSide value) {
    switch (value) {
        case RfqSide::TwoSidedQuote: return "Two Sided Quote";
        case RfqSide::BidQuote: return "Bid Quote";
        case RfqSide::AskQuote: return "Ask Quote";
        case RfqSide::Crossing: return "Crossing";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RfqSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
