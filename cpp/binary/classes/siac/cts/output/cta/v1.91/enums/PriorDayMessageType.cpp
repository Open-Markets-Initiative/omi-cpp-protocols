#include "PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(PriorDayMessageType value) {
    switch (value) {
        case PriorDayMessageType::PriorDayTradeCorrectionMessage: return "Prior Day Trade Correction Message";
        case PriorDayMessageType::PriorDayTradeMessage: return "Prior Day Trade Message";
        case PriorDayMessageType::PriorDayTradeCancelErrorMessage: return "Prior Day Trade Cancel Error Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriorDayMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
