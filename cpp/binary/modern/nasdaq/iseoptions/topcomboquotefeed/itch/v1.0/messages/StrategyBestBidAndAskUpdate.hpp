#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidCustSize.hpp"
#include "../types/BidProCustSize.hpp"
#include "../types/BidNttSize.hpp"
#include "../types/BidMarketSize.hpp"
#include "../types/BidNttMarketSize.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskCustSize.hpp"
#include "../types/AskProCustSize.hpp"
#include "../types/AskNttSize.hpp"
#include "../types/AskMarketSize.hpp"
#include "../types/AskNttMarketSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

// The options system uses this administrative message to indicate when an strategy has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution.
struct StrategyBestBidAndAskUpdate {

    Timestamp timestamp;
    StrategyId strategy_id;
    QuoteCondition quote_condition;
    BidPrice bid_price;
    BidSize bid_size;
    BidCustSize bid_cust_size;
    BidProCustSize bid_pro_cust_size;
    BidNttSize bid_ntt_size;
    BidMarketSize bid_market_size;
    BidNttMarketSize bid_ntt_market_size;
    AskPrice ask_price;
    AskSize ask_size;
    AskCustSize ask_cust_size;
    AskProCustSize ask_pro_cust_size;
    AskNttSize ask_ntt_size;
    AskMarketSize ask_market_size;
    AskNttMarketSize ask_ntt_market_size;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static StrategyBestBidAndAskUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<StrategyBestBidAndAskUpdate*>(buffer);
    }

    // parse method const
    static const StrategyBestBidAndAskUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrategyBestBidAndAskUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StrategyBestBidAndAskUpdate* parse(const MessageHeader* header) {
        return reinterpret_cast<const StrategyBestBidAndAskUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
