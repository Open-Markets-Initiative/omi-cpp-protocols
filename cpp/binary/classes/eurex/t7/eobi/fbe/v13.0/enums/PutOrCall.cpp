#include "PutOrCall.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(PutOrCall value) {
    switch (value) {
        case PutOrCall::Put: return "Put";
        case PutOrCall::Call: return "Call";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PutOrCall value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
