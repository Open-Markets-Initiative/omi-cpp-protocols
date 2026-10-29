#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/AllocId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AllocReportId.hpp"
#include "../types/AllocTransType.hpp"
#include "../types/AllocReportType.hpp"
#include "../types/AllocNoOrdersType.hpp"
#include "../types/AllocRejCode.hpp"
#include "../types/Quantity.hpp"
#include "../types/AllocStatus.hpp"
#include "../types/TradeDateOptional.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Side.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

#pragma pack(push, 1)

// AllocationReportMessage
struct AllocationReportMessage {

    OutboundBusinessHeader outbound_business_header;
    AllocId alloc_id;
    SecurityId security_id;
    AllocReportId alloc_report_id;
    AllocTransType alloc_trans_type;
    AllocReportType alloc_report_type;
    AllocNoOrdersType alloc_no_orders_type;
    AllocRejCode alloc_rej_code;
    Quantity quantity;
    AllocStatus alloc_status;
    TradeDateOptional trade_date_optional;
    TransactTime transact_time;
    Side side;
    SenderLocation sender_location;
    EnteringTrader entering_trader;

    // parse method
    static AllocationReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AllocationReportMessage*>(buffer);
    }

    // parse method const
    static const AllocationReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AllocationReportMessage*>(buffer);
    }
};

#pragma pack(pop)
}
