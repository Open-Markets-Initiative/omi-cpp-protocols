#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/PosReqIdOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PosMaintRptId.hpp"
#include "../types/PosTransType.hpp"
#include "../types/PosMaintAction.hpp"
#include "../types/PosMaintStatus.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/OrigPosReqRefId.hpp"
#include "../types/AccountType.hpp"
#include "../types/ClearingBusinessDate.hpp"
#include "../types/ThresholdAmount.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/PosMaintResult.hpp"
#include "../types/ContraryInstructionIndicator.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// PositionMaintenanceReportMessage
struct PositionMaintenanceReportMessage {

    OutboundBusinessHeader outbound_business_header;
    PosReqIdOptional pos_req_id_optional;
    SecurityId security_id;
    PosMaintRptId pos_maint_rpt_id;
    PosTransType pos_trans_type;
    PosMaintAction pos_maint_action;
    PosMaintStatus pos_maint_status;
    TradeIdOptional trade_id_optional;
    OrigPosReqRefId orig_pos_req_ref_id;
    AccountType account_type;
    ClearingBusinessDate clearing_business_date;
    ThresholdAmount threshold_amount;
    TransactTime transact_time;
    Account account;
    SenderLocation sender_location;
    PosMaintResult pos_maint_result;
    ContraryInstructionIndicator contrary_instruction_indicator;

    // parse method
    static PositionMaintenanceReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PositionMaintenanceReportMessage*>(buffer);
    }

    // parse method const
    static const PositionMaintenanceReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PositionMaintenanceReportMessage*>(buffer);
    }
};

#pragma pack(pop)
}
