#pragma once

#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad4.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Provides updates on the trading state for all instruments in a particular product.
struct ProductStateChangeMessage {

    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    TradSesStatus trad_ses_status;
    FastMarketIndicator fast_market_indicator;
    Pad4 pad_4;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13300;

    // parse method
    static ProductStateChangeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ProductStateChangeMessage*>(buffer);
    }

    // parse method const
    static const ProductStateChangeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ProductStateChangeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ProductStateChangeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ProductStateChangeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
