#include "SessionIndicator.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(SessionIndicator value) {
    switch (value) {
        case SessionIndicator::Regular: return "Regular";
        case SessionIndicator::PreMarket: return "Pre Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SessionIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace siac::opra::output::obi::v6_2
