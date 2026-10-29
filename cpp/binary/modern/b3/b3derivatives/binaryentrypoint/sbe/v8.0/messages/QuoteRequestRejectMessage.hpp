#pragma once

#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/QuoteRequestRejectReason.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/OrderQtyOptional.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRateOptional.hpp"
#include "../types/DaysToSettlementOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// QuoteRequestRejectMessage
struct QuoteRequestRejectMessage {

    BidirectionalBusinessHeader bidirectional_business_header;
    QuoteRequestRejectReason quote_request_reject_reason;
    SecurityId security_id;
    QuoteIdOptional quote_id_optional;
    TradeIdOptional trade_id_optional;
    ContraBroker contra_broker;
    TransactTime transact_time;
    EnteringTrader entering_trader;
    SettlTypeOptional settl_type_optional;
    PriceOptional price_optional;
    OrderQtyOptional order_qty_optional;
    SenderLocation sender_location;
    ExecutingTrader executing_trader;
    FixedRateOptional fixed_rate_optional;
    DaysToSettlementOptional days_to_settlement_optional;

    // parse method
    static QuoteRequestRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteRequestRejectMessage*>(buffer);
    }

    // parse method const
    static const QuoteRequestRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteRequestRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
