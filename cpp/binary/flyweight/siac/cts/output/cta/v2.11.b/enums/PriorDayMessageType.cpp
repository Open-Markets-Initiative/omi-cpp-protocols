#include "PriorDayMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(PriorDayMessageType value) {
    switch (value) {
        case PriorDayMessageType::PriorDayTradeCorrection: return "Prior Day Trade Correction";
        case PriorDayMessageType::FractionalPriorDayTradeCorrection: return "Fractional Prior Day Trade Correction";
        case PriorDayMessageType::PriorDayTrade: return "Prior Day Trade";
        case PriorDayMessageType::FractionalPriorDayTrade: return "Fractional Prior Day Trade";
        case PriorDayMessageType::PriorDayTradeCancelError: return "Prior Day Trade Cancel Error";
        case PriorDayMessageType::FractionalPriorDayTradeCancelError: return "Fractional Prior Day Trade Cancel Error";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriorDayMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
