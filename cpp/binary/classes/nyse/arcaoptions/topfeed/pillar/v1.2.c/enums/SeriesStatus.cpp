#include "SeriesStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(SeriesStatus value) {
    switch (value) {
        case SeriesStatus::TradingHalt: return "Trading Halt";
        case SeriesStatus::Resume: return "Resume";
        case SeriesStatus::Suspend: return "Suspend";
        case SeriesStatus::PreOpening: return "Pre Opening";
        case SeriesStatus::BeginAcceptingOrders: return "Begin Accepting Orders";
        case SeriesStatus::CoreSession: return "Core Session";
        case SeriesStatus::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SeriesStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
