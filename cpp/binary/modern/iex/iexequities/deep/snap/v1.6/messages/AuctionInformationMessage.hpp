#pragma once

#include "../types/AuctionType.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/IndicativeClearingPrice.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ExtensionNumber.hpp"
#include "../types/ScheduledAuctionTime.hpp"
#include "../types/AuctionBookClearingPrice.hpp"
#include "../types/CollarReferencePrice.hpp"
#include "../types/LowerAuctionCollar.hpp"
#include "../types/UpperAuctionCollar.hpp"
#include "../messages/SnapshotDataMessage.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

#pragma pack(push, 1)

// Broadcasts an Auction Information Message every one second between the Lock-in Time and the auction match for Opening and Closing Auctions, and during the Display Only Period for IPO, Halt, and Volatility Auctions.
struct AuctionInformationMessage {

    AuctionType auction_type;
    Timestamp timestamp;
    Symbol symbol;
    PairedShares paired_shares;
    ReferencePrice reference_price;
    IndicativeClearingPrice indicative_clearing_price;
    ImbalanceShares imbalance_shares;
    ImbalanceSide imbalance_side;
    ExtensionNumber extension_number;
    ScheduledAuctionTime scheduled_auction_time;
    AuctionBookClearingPrice auction_book_clearing_price;
    CollarReferencePrice collar_reference_price;
    LowerAuctionCollar lower_auction_collar;
    UpperAuctionCollar upper_auction_collar;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static AuctionInformationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionInformationMessage*>(buffer);
    }

    // parse method const
    static const AuctionInformationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionInformationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionInformationMessage* parse(const SnapshotDataMessage* header) {
        return reinterpret_cast<const AuctionInformationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SnapshotDataMessage));
    }
};

#pragma pack(pop)
}
