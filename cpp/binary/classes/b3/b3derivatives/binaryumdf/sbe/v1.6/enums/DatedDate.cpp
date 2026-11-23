// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: enums/DatedDate.cpp
#include "DatedDate.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(DatedDate value) {
    switch (value) {
        case DatedDate::NoEndDate: return "No End Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, DatedDate value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
