// Databento.MarketData.Normalized.Dbn.v3: enums/IsShortSellRestricted.cpp
#include "IsShortSellRestricted.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(IsShortSellRestricted value) {
    switch (value) {
        case IsShortSellRestricted::NotAvailable: return "Not Available";
        case IsShortSellRestricted::No: return "No";
        case IsShortSellRestricted::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IsShortSellRestricted value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
