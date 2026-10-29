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
#include "../types/TradeId.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/OrderId.hpp"
#include "../types/AggressorIndicator.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/TradeDate.hpp"
#include "../types/DaysToSettlementOptional.hpp"
#include "../types/Offset118Padding2.hpp"
#include "../types/SecondaryExecId.hpp"
#include "../types/ExecRefId.hpp"
#include "../types/FixedRatePercentage8Optional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// ExecutionReport_ForwardMessage
struct ExecutionReportForwardMessage {

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
    TradeId trade_id;
    ContraBroker contra_broker;
    OrderId order_id;
    AggressorIndicator aggressor_indicator;
    SettlTypeOptional settl_type_optional;
    TradeDate trade_date;
    DaysToSettlementOptional days_to_settlement_optional;
    Offset118Padding2 offset_118_padding_2;
    SecondaryExecId secondary_exec_id;
    ExecRefId exec_ref_id;
    FixedRatePercentage8Optional fixed_rate_percentage_8_optional;
    OrderQty order_qty;
    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    SecurityTradingStatus security_trading_status;
    TradingSubAccount trading_sub_account;

    // parse method
    static ExecutionReportForwardMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionReportForwardMessage*>(buffer);
    }

    // parse method const
    static const ExecutionReportForwardMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionReportForwardMessage*>(buffer);
    }
};

#pragma pack(pop)
}
