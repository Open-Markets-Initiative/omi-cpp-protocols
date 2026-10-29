#include "PrintableFlag.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(PrintableFlag value) {
    switch (value) {
        case PrintableFlag::NotPrinted: return "Not Printed";
        case PrintableFlag::Printed: return "Printed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PrintableFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
