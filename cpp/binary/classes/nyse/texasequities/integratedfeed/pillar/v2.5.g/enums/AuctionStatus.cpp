#include "AuctionStatus.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(AuctionStatus value) {
    switch (value) {
        case AuctionStatus::WillRunAsAlwaysForOpenAndClose: return "Will Run As Always For Open And Close";
        case AuctionStatus::WillRunInterestExistsInsideOrAtTheCollarsOrIsFullyPairedOff: return "Will Run Interest Exists Inside Or At The Collars Or Is Fully Paired Off";
        case AuctionStatus::WillNotRunBecauseThereIsAnImbalanceThroughTheCollars: return "Will Not Run Because There Is An Imbalance Through The Collars";
        case AuctionStatus::WillNotRunWillTransitionToTheClosingAuctionInstead: return "Will Not Run Will Transition To The Closing Auction Instead";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
