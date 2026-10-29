#include "MmProtectionReset.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(MmProtectionReset value) {
    switch (value) {
        case MmProtectionReset::FalseValue: return "False Value";
        case MmProtectionReset::TrueValue: return "True Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MmProtectionReset value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
