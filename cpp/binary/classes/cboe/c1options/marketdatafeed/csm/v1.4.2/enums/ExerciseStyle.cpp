#include "ExerciseStyle.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(ExerciseStyle value) {
    switch (value) {
        case ExerciseStyle::American: return "American";
        case ExerciseStyle::European: return "European";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ExerciseStyle value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
