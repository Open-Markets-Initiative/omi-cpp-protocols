#include "CompletionIndicator.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(CompletionIndicator value) {
    switch (value) {
        case CompletionIndicator::Incomplete: return "Incomplete";
        case CompletionIndicator::Complete: return "Complete";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CompletionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
