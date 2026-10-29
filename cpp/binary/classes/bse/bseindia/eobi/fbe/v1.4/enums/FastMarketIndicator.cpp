#include "FastMarketIndicator.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

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

} // namespace bse::bseindia::eobi::fbe::v1_4
