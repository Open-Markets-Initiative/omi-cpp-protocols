#include "TradeThroughExemptIndicator.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(TradeThroughExemptIndicator value) {
    switch (value) {
        case TradeThroughExemptIndicator::NotATradeThroughExemption: return "Not A Trade Through Exemption";
        case TradeThroughExemptIndicator::TradeThroughExemption: return "Trade Through Exemption";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeThroughExemptIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
