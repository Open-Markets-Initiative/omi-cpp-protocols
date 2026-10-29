#include "FastMarketIndicator.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

std::string_view to_string(FastMarketIndicator value) {
    switch (value) {
        case FastMarketIndicator::No: return "No";
        case FastMarketIndicator::Yes: return "Yes";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FastMarketIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v3_0
