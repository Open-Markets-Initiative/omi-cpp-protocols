#include "ShortSaleThresholdIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(ShortSaleThresholdIndicator value) {
    switch (value) {
        case ShortSaleThresholdIndicator::Restricted: return "Restricted";
        case ShortSaleThresholdIndicator::NotRestricted: return "Not Restricted";
        case ShortSaleThresholdIndicator::NotAvailable: return "Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSaleThresholdIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
