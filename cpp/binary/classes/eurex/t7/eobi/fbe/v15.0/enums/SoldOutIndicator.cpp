#include "SoldOutIndicator.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(SoldOutIndicator value) {
    switch (value) {
        case SoldOutIndicator::SoldOut: return "Sold Out";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SoldOutIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
