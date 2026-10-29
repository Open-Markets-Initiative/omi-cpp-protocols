#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/CxlRejResponseTo.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecondaryOrderIdOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrdRejReason.hpp"
#include "../types/TransactTime.hpp"
#include "../types/ExecId.hpp"
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../types/Account.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQtyOptional.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/CrossidOptional.hpp"
#include "../types/CrossedIndicator.hpp"
#include "../types/ReceivedTime.hpp"
#include "../types/Offset146Padding3.hpp"
#include "../types/Ordtagid.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/StrategyId.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// ExecutionReport_RejectMessage
struct ExecutionReportRejectMessage {

    OutboundBusinessHeader outbound_business_header;
    Side side;
    CxlRejResponseTo cxl_rej_response_to;
    Clordid clordid;
    SecondaryOrderIdOptional secondary_order_id_optional;
    SecurityId security_id;
    OrdRejReason ord_rej_reason;
    TransactTime transact_time;
    ExecId exec_id;
    OrderIdOptional order_id_optional;
    Origclordid origclordid;
    Account account;
    Ordtype ordtype;
    TimeInForce time_in_force;
    ExpireDate expire_date;
    OrderQtyOptional order_qty_optional;
    PriceOptional price_optional;
    StopPx stop_px;
    MinQty min_qty;
    MaxFloor max_floor;
    CrossidOptional crossid_optional;
    CrossedIndicator crossed_indicator;
    ReceivedTime received_time;
    Offset146Padding3 offset_146_padding_3;
    Ordtagid ordtagid;
    InvestorId investor_id;
    StrategyId strategy_id;
    TradingSubAccount trading_sub_account;

    // parse method
    static ExecutionReportRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionReportRejectMessage*>(buffer);
    }

    // parse method const
    static const ExecutionReportRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionReportRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
