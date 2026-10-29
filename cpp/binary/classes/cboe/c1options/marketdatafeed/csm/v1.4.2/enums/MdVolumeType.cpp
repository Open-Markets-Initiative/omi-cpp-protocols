#include "MdVolumeType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(MdVolumeType value) {
    switch (value) {
        case MdVolumeType::TotalLimit: return "Total Limit";
        case MdVolumeType::CustomerLimit: return "Customer Limit";
        case MdVolumeType::TotalContingencyAllOrNone: return "Total Contingency All Or None";
        case MdVolumeType::CustomerContingencyAllOrNone: return "Customer Contingency All Or None";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdVolumeType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
