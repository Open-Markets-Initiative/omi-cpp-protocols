#include "PosTransType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(PosTransType value) {
    switch (value) {
        case PosTransType::Exercise: return "Exercise";
        case PosTransType::AutomaticExercise: return "Automatic Exercise";
        case PosTransType::ExerciseNotAutomatic: return "Exercise Not Automatic";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PosTransType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
