#include "FinraBboIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(FinraBboIndicator value) {
    switch (value) {
        case FinraBboIndicator::NotApplicable: return "Not Applicable";
        case FinraBboIndicator::NoFinraBboChange: return "No Finra Bbo Change";
        case FinraBboIndicator::NoFinraBboExists: return "No Finra Bbo Exists";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinraBboIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
