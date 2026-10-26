#include "LotType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

std::string_view to_string(LotType value) {
    switch (value) {
        case LotType::OddLot: return "Odd Lot";
        case LotType::RoundLot: return "Round Lot";
        case LotType::BlockLot: return "Block Lot";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LotType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
