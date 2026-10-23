#include "UnderlyingSecurityAltIdSource.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(UnderlyingSecurityAltIdSource value) {
    switch (value) {
        case UnderlyingSecurityAltIdSource::Cusip: return "Cusip";
        case UnderlyingSecurityAltIdSource::Isin: return "Isin";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnderlyingSecurityAltIdSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
