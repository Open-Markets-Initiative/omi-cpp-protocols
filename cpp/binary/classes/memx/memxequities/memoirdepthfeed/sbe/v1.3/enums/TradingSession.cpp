#include "TradingSession.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(TradingSession value) {
    switch (value) {
        case TradingSession::Opening: return "Opening";
        case TradingSession::Trading: return "Trading";
        case TradingSession::PostTrading: return "Post Trading";
        case TradingSession::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSession value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
