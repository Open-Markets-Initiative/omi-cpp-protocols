#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/OrdStatus.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/CumQty.hpp"
#include "../types/Account.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MarketSegmentReceivedTime.hpp"
#include "../types/OrderId.hpp"
#include "../types/Origclordid.hpp"
#include "../types/TradeDate.hpp"
#include "../types/WorkingIndicator.hpp"
#include "../types/ExecRestatementReason.hpp"
#include "../types/Offset100Padding4.hpp"
#include "../types/MassActionReportIdOptional.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/ReceivedTime.hpp"
#include "../types/Offset164Padding3.hpp"
#include "../types/Ordtagid.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/StrategyId.hpp"
#include "../types/ActionRequestedFromSessionId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// ExecutionReport_CancelMessage
struct ExecutionReportCancelMessage {

    OutboundBusinessHeader outbound_business_header;
    Side side;
    OrdStatus ord_status;
    Clordid clordid;
    SecondaryOrderId secondary_order_id;
    SecurityId security_id;
    CumQty cum_qty;
    Account account;
    ExecId exec_id;
    TransactTime transact_time;
    MarketSegmentReceivedTime market_segment_received_time;
    OrderId order_id;
    Origclordid origclordid;
    TradeDate trade_date;
    WorkingIndicator working_indicator;
    ExecRestatementReason exec_restatement_reason;
    Offset100Padding4 offset_100_padding_4;
    MassActionReportIdOptional mass_action_report_id_optional;
    Ordtype ordtype;
    TimeInForce time_in_force;
    ExpireDate expire_date;
    OrderQty order_qty;
    PriceOptional price_optional;
    StopPx stop_px;
    MinQty min_qty;
    MaxFloor max_floor;
    ReceivedTime received_time;
    Offset164Padding3 offset_164_padding_3;
    Ordtagid ordtagid;
    InvestorId investor_id;
    StrategyId strategy_id;
    ActionRequestedFromSessionId action_requested_from_session_id;

    // parse method
    static ExecutionReportCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionReportCancelMessage*>(buffer);
    }

    // parse method const
    static const ExecutionReportCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionReportCancelMessage*>(buffer);
    }
};

#pragma pack(pop)
}
