#include "BidOrdType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(BidOrdType value) {
    switch (value) {
        case BidOrdType::Market: return "Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BidOrdType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
