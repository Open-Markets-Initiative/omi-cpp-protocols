#include "MmProtectionResetOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(MmProtectionResetOptional value) {
    switch (value) {
        case MmProtectionResetOptional::FalseValue: return "False Value";
        case MmProtectionResetOptional::TrueValue: return "True Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MmProtectionResetOptional value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
