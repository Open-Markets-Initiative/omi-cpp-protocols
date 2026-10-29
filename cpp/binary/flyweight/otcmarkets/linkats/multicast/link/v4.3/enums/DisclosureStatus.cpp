#include "DisclosureStatus.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(DisclosureStatus value) {
    switch (value) {
        case DisclosureStatus::NoDisclosure: return "No Disclosure";
        case DisclosureStatus::CurrentInformation: return "Current Information";
        case DisclosureStatus::LimitedInformation: return "Limited Information";
        case DisclosureStatus::NoInformation: return "No Information";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, DisclosureStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
