#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad7.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct ProductSummary {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    TradSesStatus trad_ses_status;
    MarketCondition market_condition;
    FastMarketIndicator fast_market_indicator;
    Pad7 pad7;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13600;

    // parse method
    static ProductSummary* parse(std::byte* buffer) {
        return reinterpret_cast<ProductSummary*>(buffer);
    }

    // parse method const
    static const ProductSummary* parse(const std::byte* buffer) {
        return reinterpret_cast<const ProductSummary*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ProductSummary* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const ProductSummary*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
