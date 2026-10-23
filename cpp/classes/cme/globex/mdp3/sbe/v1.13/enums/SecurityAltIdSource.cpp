#include "SecurityAltIdSource.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

std::string_view to_string(SecurityAltIdSource value) {
    switch (value) {
        case SecurityAltIdSource::Cusip: return "Cusip";
        case SecurityAltIdSource::Isin: return "Isin";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityAltIdSource value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_13
