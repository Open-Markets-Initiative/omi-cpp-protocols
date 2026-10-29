#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/OrdStatus.hpp"
#include "../types/ClordidOptional.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Account.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LeavesQty.hpp"
#include "../types/CumQty.hpp"
#include "../types/AggressorIndicator.hpp"
#include "../types/ExecType.hpp"
#include "../types/OrderCategory.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TotNoRelatedSym.hpp"
#include "../types/Offset119Padding1.hpp"
#include "../types/SecondaryExecId.hpp"
#include "../types/ExecRefId.hpp"
#include "../types/CrossidOptional.hpp"
#include "../types/CrossedIndicator.hpp"
#include "../types/OrderQty.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/CrossType.hpp"
#include "../types/CrossPrioritization.hpp"
#include "../types/Offset159Padding1.hpp"
#include "../types/StrategyId.hpp"
#include "../structs/ImpliedEventId.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// ExecutionReport_TradeMessage
struct ExecutionReportTradeMessage {

    OutboundBusinessHeader outbound_business_header;
    Side side;
    OrdStatus ord_status;
    ClordidOptional clordid_optional;
    SecondaryOrderId secondary_order_id;
    SecurityId security_id;
    Account account;
    LastQty last_qty;
    LastPx last_px;
    ExecId exec_id;
    TransactTime transact_time;
    LeavesQty leaves_qty;
    CumQty cum_qty;
    AggressorIndicator aggressor_indicator;
    ExecType exec_type;
    OrderCategory order_category;
    MultiLegReportingType multi_leg_reporting_type;
    TradeId trade_id;
    ContraBroker contra_broker;
    OrderId order_id;
    TradeDate trade_date;
    TotNoRelatedSym tot_no_related_sym;
    Offset119Padding1 offset_119_padding_1;
    SecondaryExecId secondary_exec_id;
    ExecRefId exec_ref_id;
    CrossidOptional crossid_optional;
    CrossedIndicator crossed_indicator;
    OrderQty order_qty;
    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    SecurityTradingStatus security_trading_status;
    CrossType cross_type;
    CrossPrioritization cross_prioritization;
    Offset159Padding1 offset_159_padding_1;
    StrategyId strategy_id;
    ImpliedEventId implied_event_id;
    TradingSubAccount trading_sub_account;

    // parse method
    static ExecutionReportTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionReportTradeMessage*>(buffer);
    }

    // parse method const
    static const ExecutionReportTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionReportTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
