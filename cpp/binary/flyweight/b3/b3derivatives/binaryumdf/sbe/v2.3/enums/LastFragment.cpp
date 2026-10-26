#include "LastFragment.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(LastFragment value) {
    switch (value) {
        case LastFragment::FalseValue: return "False Value";
        case LastFragment::TrueValue: return "True Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LastFragment value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
