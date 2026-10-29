#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/OrdStatus.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LeavesQty.hpp"
#include "../types/Account.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/CumQty.hpp"
#include "../types/MarketSegmentReceivedTime.hpp"
#include "../types/OrderId.hpp"
#include "../types/Origclordid.hpp"
#include "../types/ProtectionPrice.hpp"
#include "../types/TradeDate.hpp"
#include "../types/WorkingIndicator.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// ExecutionReport_ModifyMessage
struct ExecutionReportModifyMessage {

    OutboundBusinessHeader outbound_business_header;
    Side side;
    OrdStatus ord_status;
    Clordid clordid;
    SecondaryOrderId secondary_order_id;
    SecurityId security_id;
    LeavesQty leaves_qty;
    Account account;
    ExecId exec_id;
    TransactTime transact_time;
    CumQty cum_qty;
    MarketSegmentReceivedTime market_segment_received_time;
    OrderId order_id;
    Origclordid origclordid;
    ProtectionPrice protection_price;
    TradeDate trade_date;
    WorkingIndicator working_indicator;
    MultiLegReportingType multi_leg_reporting_type;
    Ordtype ordtype;
    TimeInForce time_in_force;
    ExpireDate expire_date;
    OrderQty order_qty;
    PriceOptional price_optional;
    StopPx stop_px;
    MinQty min_qty;
    MaxFloor max_floor;

    // parse method
    static ExecutionReportModifyMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionReportModifyMessage*>(buffer);
    }

    // parse method const
    static const ExecutionReportModifyMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionReportModifyMessage*>(buffer);
    }
};

#pragma pack(pop)
}
