#include "MdControlType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(MdControlType value) {
    switch (value) {
        case MdControlType::StartOfSummary: return "Start Of Summary";
        case MdControlType::EndOfSummary: return "End Of Summary";
        case MdControlType::StartOfSettlement: return "Start Of Settlement";
        case MdControlType::EndOfSettlement: return "End Of Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdControlType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
