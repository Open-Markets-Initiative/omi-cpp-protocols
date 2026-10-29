#include "PriceResolution.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(PriceResolution value) {
    switch (value) {
        case PriceResolution::AllPenny: return "All Penny";
        case PriceResolution::PennyNickel: return "Penny Nickel";
        case PriceResolution::NickelDime: return "Nickel Dime";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceResolution value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
