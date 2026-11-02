#include "IsTrading.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(IsTrading value) {
    switch (value) {
        case IsTrading::NotAvailable: return "Not Available";
        case IsTrading::No: return "No";
        case IsTrading::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsTrading value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
