#include "ImpliedMarketIndicator.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

std::string_view to_string(ImpliedMarketIndicator value) {
    switch (value) {
        case ImpliedMarketIndicator::NotImplied: return "Not Implied";
        case ImpliedMarketIndicator::Implied: return "Implied";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImpliedMarketIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
