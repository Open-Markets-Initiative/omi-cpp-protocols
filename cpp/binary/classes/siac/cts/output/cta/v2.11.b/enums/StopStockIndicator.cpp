#include "StopStockIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(StopStockIndicator value) {
    switch (value) {
        case StopStockIndicator::StopStockNotApplicable: return "Stop Stock Not Applicable";
        case StopStockIndicator::StopStock: return "Stop Stock";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StopStockIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
