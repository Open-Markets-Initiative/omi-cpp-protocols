#include "OptPayoutType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

std::string_view to_string(OptPayoutType value) {
    switch (value) {
        case OptPayoutType::Vanilla: return "Vanilla";
        case OptPayoutType::Capped: return "Capped";
        case OptPayoutType::Binary: return "Binary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OptPayoutType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
