#include "MassSoldOutIndicator.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(MassSoldOutIndicator value) {
    switch (value) {
        case MassSoldOutIndicator::SoldOut: return "Sold Out";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassSoldOutIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
