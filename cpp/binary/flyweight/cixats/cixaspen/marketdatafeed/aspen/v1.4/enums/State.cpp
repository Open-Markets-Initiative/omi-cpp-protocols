#include "State.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::string_view to_string(State value) {
    switch (value) {
        case State::Halted: return "Halted";
        case State::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, State value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
