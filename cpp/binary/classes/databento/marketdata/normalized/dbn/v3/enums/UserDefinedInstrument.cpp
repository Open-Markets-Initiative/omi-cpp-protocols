// Databento.MarketData.Normalized.Dbn.v3: enums/UserDefinedInstrument.cpp
#include "UserDefinedInstrument.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(UserDefinedInstrument value) {
    switch (value) {
        case UserDefinedInstrument::No: return "No";
        case UserDefinedInstrument::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UserDefinedInstrument value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace databento::marketdata::normalized::dbn::v3
