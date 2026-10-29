#include "PrintableFlag.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(PrintableFlag value) {
    switch (value) {
        case PrintableFlag::NotPrintedToTheSip: return "Not Printed To The Sip";
        case PrintableFlag::PrintedToTheSip: return "Printed To The Sip";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrintableFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
