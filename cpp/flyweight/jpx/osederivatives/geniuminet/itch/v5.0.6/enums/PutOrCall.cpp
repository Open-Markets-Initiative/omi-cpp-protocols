#include "PutOrCall.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(PutOrCall value) {
    switch (value) {
        case PutOrCall::Call: return "Call";
        case PutOrCall::Put: return "Put";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PutOrCall value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
