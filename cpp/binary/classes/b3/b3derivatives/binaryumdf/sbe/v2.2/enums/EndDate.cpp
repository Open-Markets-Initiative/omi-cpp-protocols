// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: enums/EndDate.cpp
#include "EndDate.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

std::string_view to_string(EndDate value) {
    switch (value) {
        case EndDate::NoEndDate: return "No End Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EndDate value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
