#include "CommunicationStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(CommunicationStartEndFlag value) {
    switch (value) {
        case CommunicationStartEndFlag::HealthCheckControl: return "Health Check Control";
        case CommunicationStartEndFlag::CommunicationStart: return "Communication Start";
        case CommunicationStartEndFlag::CommunicationEnd: return "Communication End";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CommunicationStartEndFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
