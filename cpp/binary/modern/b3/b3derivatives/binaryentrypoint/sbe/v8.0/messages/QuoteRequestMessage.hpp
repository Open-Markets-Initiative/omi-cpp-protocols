#pragma once

#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Price.hpp"
#include "../types/SettlType.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/OrderQty.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRate.hpp"
#include "../types/DaysToSettlement.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// QuoteRequestMessage
struct QuoteRequestMessage {

    BidirectionalBusinessHeader bidirectional_business_header;
    SecurityId security_id;
    QuoteIdOptional quote_id_optional;
    TradeIdOptional trade_id_optional;
    ContraBroker contra_broker;
    TransactTime transact_time;
    Price price;
    SettlType settl_type;
    ExecuteUnderlyingTrade execute_underlying_trade;
    OrderQty order_qty;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTrader executing_trader;
    FixedRate fixed_rate;
    DaysToSettlement days_to_settlement;

    // parse method
    static QuoteRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteRequestMessage*>(buffer);
    }

    // parse method const
    static const QuoteRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
