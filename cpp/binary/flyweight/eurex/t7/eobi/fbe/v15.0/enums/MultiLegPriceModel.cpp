#include "MultiLegPriceModel.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(MultiLegPriceModel value) {
    switch (value) {
        case MultiLegPriceModel::Standard: return "Standard";
        case MultiLegPriceModel::UserDefined: return "User Defined";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MultiLegPriceModel value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
