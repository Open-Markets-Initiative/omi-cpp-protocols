#include "LotType.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(LotType value) {
    switch (value) {
        case LotType::Undefined: return "Undefined";
        case LotType::OddLot: return "Odd Lot";
        case LotType::RoundLot: return "Round Lot";
        case LotType::BlockLot: return "Block Lot";
        case LotType::AllOrNoneLot: return "All Or None Lot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LotType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
