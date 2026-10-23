#include "AlgorithmicTradeIndicator.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(AlgorithmicTradeIndicator value) {
    switch (value) {
        case AlgorithmicTradeIndicator::AlgorithmicTrade: return "Algorithmic Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AlgorithmicTradeIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
