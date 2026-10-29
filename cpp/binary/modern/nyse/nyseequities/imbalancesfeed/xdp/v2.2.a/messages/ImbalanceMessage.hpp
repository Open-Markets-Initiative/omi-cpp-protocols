#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/PairedQty.hpp"
#include "../types/TotalImbalanceQty.hpp"
#include "../types/MarketImbalanceQty.hpp"
#include "../types/AuctionTime.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ContinuousBookClearingPrice.hpp"
#include "../types/ClosingOnlyClearingPrice.hpp"
#include "../types/SsrFilingPrice.hpp"
#include "../types/IndicativeMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/AuctionStatus.hpp"
#include "../types/FreezeStatus.hpp"
#include "../types/NumExtensions.hpp"
#include "../types/UnpairedQty.hpp"
#include "../types/UnpairedSide.hpp"
#include "../types/SignificantImbalance.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

#pragma pack(push, 1)

// Imbalance messages are sent periodically during auctions to update price and volume information. If there is no change to the calculated fields, no message will be generated.
struct ImbalanceMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    ReferencePrice reference_price;
    PairedQty paired_qty;
    TotalImbalanceQty total_imbalance_qty;
    MarketImbalanceQty market_imbalance_qty;
    AuctionTime auction_time;
    AuctionType auction_type;
    ImbalanceSide imbalance_side;
    ContinuousBookClearingPrice continuous_book_clearing_price;
    ClosingOnlyClearingPrice closing_only_clearing_price;
    SsrFilingPrice ssr_filing_price;
    IndicativeMatchPrice indicative_match_price;
    UpperCollar upper_collar;
    LowerCollar lower_collar;
    AuctionStatus auction_status;
    FreezeStatus freeze_status;
    NumExtensions num_extensions;
    UnpairedQty unpaired_qty;
    UnpairedSide unpaired_side;
    SignificantImbalance significant_imbalance;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 105;

    // parse method
    static ImbalanceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ImbalanceMessage*>(buffer);
    }

    // parse method const
    static const ImbalanceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImbalanceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ImbalanceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ImbalanceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
