// B3.B3Derivatives.BinaryUmdf.Sbe.v1.6: enums/IssueDate.cpp
#include "IssueDate.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

std::string_view to_string(IssueDate value) {
    switch (value) {
        case IssueDate::NoEndDate: return "No End Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IssueDate value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
