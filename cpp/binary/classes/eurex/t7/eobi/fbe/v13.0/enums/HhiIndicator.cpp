#include "HhiIndicator.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(HhiIndicator value) {
    switch (value) {
        case HhiIndicator::NoUpdate: return "No Update";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HhiIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
