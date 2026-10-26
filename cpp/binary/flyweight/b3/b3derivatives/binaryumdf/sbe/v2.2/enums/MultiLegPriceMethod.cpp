#include "MultiLegPriceMethod.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

std::string_view to_string(MultiLegPriceMethod value) {
    switch (value) {
        case MultiLegPriceMethod::NetPrice: return "Net Price";
        case MultiLegPriceMethod::ReversedNetPrice: return "Reversed Net Price";
        case MultiLegPriceMethod::YieldDifference: return "Yield Difference";
        case MultiLegPriceMethod::Individual: return "Individual";
        case MultiLegPriceMethod::ContractWeightedAveragePrice: return "Contract Weighted Average Price";
        case MultiLegPriceMethod::MultipliedPrice: return "Multiplied Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MultiLegPriceMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
