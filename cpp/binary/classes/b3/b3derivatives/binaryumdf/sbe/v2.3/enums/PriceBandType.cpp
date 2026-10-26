#include "PriceBandType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(PriceBandType value) {
    switch (value) {
        case PriceBandType::HardLimit: return "Hard Limit";
        case PriceBandType::AuctionLimits: return "Auction Limits";
        case PriceBandType::RejectionBand: return "Rejection Band";
        case PriceBandType::StaticLimits: return "Static Limits";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PriceBandType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
