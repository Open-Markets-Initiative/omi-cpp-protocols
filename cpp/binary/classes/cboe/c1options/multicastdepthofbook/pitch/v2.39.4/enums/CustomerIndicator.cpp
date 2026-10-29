#include "CustomerIndicator.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

std::string_view to_string(CustomerIndicator value) {
    switch (value) {
        case CustomerIndicator::NonCustomer: return "Non Customer";
        case CustomerIndicator::Customer: return "Customer";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CustomerIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
