#include "UpdateAction.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

std::string_view to_string(UpdateAction value) {
    switch (value) {
        case UpdateAction::New: return "New";
        case UpdateAction::Delete: return "Delete";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UpdateAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v1
