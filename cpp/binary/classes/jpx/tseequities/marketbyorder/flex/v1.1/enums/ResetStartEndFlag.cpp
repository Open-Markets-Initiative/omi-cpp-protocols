#include "ResetStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(ResetStartEndFlag value) {
    switch (value) {
        case ResetStartEndFlag::StartOfResetDissemination: return "Start Of Reset Dissemination";
        case ResetStartEndFlag::EndOfResetDissemination: return "End Of Reset Dissemination";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ResetStartEndFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
