#include "TestSecurityIndicator.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(TestSecurityIndicator value) {
    switch (value) {
        case TestSecurityIndicator::Yes: return "Yes";
        case TestSecurityIndicator::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TestSecurityIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
