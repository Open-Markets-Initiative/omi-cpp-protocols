#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/Reserved4.hpp"
#include "../types/PairedQty.hpp"
#include "../types/TotalImbalanceQty.hpp"
#include "../types/MarketImbalanceQty.hpp"
#include "../types/Reserved2.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ContinuousBookClearingPrice.hpp"
#include "../types/AuctionInterestClearingPrice.hpp"
#include "../types/SecondReserved4.hpp"
#include "../types/IndicativeMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/AuctionStatus.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

// Options Imbalance messages are published once a second during opening and reopening auctions to update price and volume information
struct OptionsImbalanceMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SeriesIndex series_index;
    SeriesSeqNum series_seq_num;
    Reserved4 reserved_4;
    PairedQty paired_qty;
    TotalImbalanceQty total_imbalance_qty;
    MarketImbalanceQty market_imbalance_qty;
    Reserved2 reserved_2;
    AuctionType auction_type;
    ImbalanceSide imbalance_side;
    ContinuousBookClearingPrice continuous_book_clearing_price;
    AuctionInterestClearingPrice auction_interest_clearing_price;
    SecondReserved4 second_reserved_4;
    IndicativeMatchPrice indicative_match_price;
    UpperCollar upper_collar;
    LowerCollar lower_collar;
    AuctionStatus auction_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 305;

    // parse method
    static OptionsImbalanceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsImbalanceMessage*>(buffer);
    }

    // parse method const
    static const OptionsImbalanceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsImbalanceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsImbalanceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsImbalanceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
