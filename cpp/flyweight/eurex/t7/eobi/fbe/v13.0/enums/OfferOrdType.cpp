#include "OfferOrdType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(OfferOrdType value) {
    switch (value) {
        case OfferOrdType::Market: return "Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OfferOrdType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
