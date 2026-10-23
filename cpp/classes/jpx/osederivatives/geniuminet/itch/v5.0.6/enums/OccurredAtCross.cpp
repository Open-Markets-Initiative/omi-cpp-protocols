#include "OccurredAtCross.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(OccurredAtCross value) {
    switch (value) {
        case OccurredAtCross::No: return "No";
        case OccurredAtCross::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OccurredAtCross value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
