#pragma once

#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/Side.hpp"
#include "../types/SettlType.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRate.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/DaysToSettlement.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// QuoteMessage
struct QuoteMessage {

    BidirectionalBusinessHeader bidirectional_business_header;
    SecurityId security_id;
    QuoteId quote_id;
    TransactTime transact_time;
    PriceOptional price_optional;
    OrderQty order_qty;
    Side side;
    SettlType settl_type;
    Account account;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTrader executing_trader;
    FixedRate fixed_rate;
    ExecuteUnderlyingTrade execute_underlying_trade;
    DaysToSettlement days_to_settlement;

    // parse method
    static QuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteMessage*>(buffer);
    }

    // parse method const
    static const QuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
