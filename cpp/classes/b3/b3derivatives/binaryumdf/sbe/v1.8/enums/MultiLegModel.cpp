#include "MultiLegModel.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

std::string_view to_string(MultiLegModel value) {
    switch (value) {
        case MultiLegModel::Predefined: return "Predefined";
        case MultiLegModel::UserDefined: return "User Defined";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MultiLegModel value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
