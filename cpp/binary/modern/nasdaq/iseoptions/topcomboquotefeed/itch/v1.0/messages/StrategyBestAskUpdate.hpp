#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/CustSize.hpp"
#include "../types/ProCustSize.hpp"
#include "../types/NttSize.hpp"
#include "../types/MarketSize.hpp"
#include "../types/NttMarketSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

#pragma pack(push, 1)

// The options system will continuously calculate its best offer position for active strategies on the options market during the trading day. Whenever the best ask position changes on one side but not the other side, the options system will send its best ask update via this feed for the affected security
struct StrategyBestAskUpdate {

    Timestamp timestamp;
    StrategyId strategy_id;
    QuoteCondition quote_condition;
    Price price;
    Size size;
    CustSize cust_size;
    ProCustSize pro_cust_size;
    NttSize ntt_size;
    MarketSize market_size;
    NttMarketSize ntt_market_size;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static StrategyBestAskUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<StrategyBestAskUpdate*>(buffer);
    }

    // parse method const
    static const StrategyBestAskUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrategyBestAskUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StrategyBestAskUpdate* parse(const MessageHeader* header) {
        return reinterpret_cast<const StrategyBestAskUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
