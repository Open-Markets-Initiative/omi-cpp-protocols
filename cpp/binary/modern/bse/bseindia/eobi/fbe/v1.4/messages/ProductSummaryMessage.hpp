#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published once each snapshot cycle, carrying attributes that are equal for all instruments in the product.
struct ProductSummaryMessage {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    TradSesStatus trad_ses_status;
    FastMarketIndicator fast_market_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13600;

    // parse method
    static ProductSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ProductSummaryMessage*>(buffer);
    }

    // parse method const
    static const ProductSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ProductSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ProductSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ProductSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
