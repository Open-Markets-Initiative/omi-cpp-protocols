// Databento.MarketData.Normalized.Dbn.v3: enums/IsQuoting.cpp
#include "IsQuoting.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(IsQuoting value) {
    switch (value) {
        case IsQuoting::NotAvailable: return "Not Available";
        case IsQuoting::No: return "No";
        case IsQuoting::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsQuoting value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
