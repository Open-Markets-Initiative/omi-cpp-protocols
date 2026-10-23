#include "ExerciseStyle.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(ExerciseStyle value) {
    switch (value) {
        case ExerciseStyle::European: return "European";
        case ExerciseStyle::American: return "American";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExerciseStyle value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
