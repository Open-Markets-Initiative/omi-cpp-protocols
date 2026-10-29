#include "RfqStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(RfqStatus value) {
    switch (value) {
        case RfqStatus::Start: return "Start";
        case RfqStatus::End: return "End";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RfqStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
