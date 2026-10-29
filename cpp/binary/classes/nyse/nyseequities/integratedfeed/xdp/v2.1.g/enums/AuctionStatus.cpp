#include "AuctionStatus.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(AuctionStatus value) {
    switch (value) {
        case AuctionStatus::WillRunOpenClose: return "Will Run Open Close";
        case AuctionStatus::WillRunInterest: return "Will Run Interest";
        case AuctionStatus::WillNotRunImbalance: return "Will Not Run Imbalance";
        case AuctionStatus::WillNotRunTransitionToClosing: return "Will Not Run Transition To Closing";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
