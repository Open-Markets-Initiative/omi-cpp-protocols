#include "LastFragment.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(LastFragment value) {
    switch (value) {
        case LastFragment::N: return "N";
        case LastFragment::Y: return "Y";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LastFragment value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
