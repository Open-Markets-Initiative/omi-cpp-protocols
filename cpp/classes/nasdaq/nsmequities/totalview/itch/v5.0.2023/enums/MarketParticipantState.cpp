#include "MarketParticipantState.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(MarketParticipantState value) {
    switch (value) {
        case MarketParticipantState::Active: return "Active";
        case MarketParticipantState::Excused: return "Excused";
        case MarketParticipantState::Withdrawn: return "Withdrawn";
        case MarketParticipantState::Suspended: return "Suspended";
        case MarketParticipantState::Deleted: return "Deleted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketParticipantState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
