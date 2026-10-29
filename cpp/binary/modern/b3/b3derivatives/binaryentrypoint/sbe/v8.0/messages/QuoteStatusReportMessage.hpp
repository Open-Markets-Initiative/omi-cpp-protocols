#pragma once

#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/QuoteRejectReason.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteId.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/QuoteStatus.hpp"
#include "../types/QuoteStatusResponseTo.hpp"
#include "../types/Account.hpp"
#include "../types/SideOptional.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRateOptional.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/DaysToSettlementOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// QuoteStatusReportMessage
struct QuoteStatusReportMessage {

    BidirectionalBusinessHeader bidirectional_business_header;
    QuoteRejectReason quote_reject_reason;
    SecurityId security_id;
    QuoteId quote_id;
    TradeIdOptional trade_id_optional;
    ContraBroker contra_broker;
    TransactTime transact_time;
    QuoteStatus quote_status;
    QuoteStatusResponseTo quote_status_response_to;
    Account account;
    SideOptional side_optional;
    SettlTypeOptional settl_type_optional;
    PriceOptional price_optional;
    OrderQty order_qty;
    SenderLocation sender_location;
    EnteringTrader entering_trader;
    ExecutingTrader executing_trader;
    FixedRateOptional fixed_rate_optional;
    ExecuteUnderlyingTrade execute_underlying_trade;
    DaysToSettlementOptional days_to_settlement_optional;

    // parse method
    static QuoteStatusReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteStatusReportMessage*>(buffer);
    }

    // parse method const
    static const QuoteStatusReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteStatusReportMessage*>(buffer);
    }
};

#pragma pack(pop)
}
