// Databento.MarketData.Normalized.Dbn.v3: enums/Action.cpp
#include "Action.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(Action value) {
    switch (value) {
        case Action::Add: return "Add";
        case Action::Cancel: return "Cancel";
        case Action::Fill: return "Fill";
        case Action::Modify: return "Modify";
        case Action::None: return "None";
        case Action::Clear: return "Clear";
        case Action::Trade: return "Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Action value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
