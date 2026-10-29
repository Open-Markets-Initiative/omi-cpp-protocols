#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/PosReqId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/ThresholdAmount.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/PosTransType.hpp"
#include "../types/ClearingBusinessDate.hpp"
#include "../types/ContraryInstructionIndicator.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/LongQty.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// PositionMaintenanceRequestMessage
struct PositionMaintenanceRequestMessage {

    InboundBusinessHeader inbound_business_header;
    PosReqId pos_req_id;
    SecurityId security_id;
    ThresholdAmount threshold_amount;
    Account account;
    SenderLocation sender_location;
    PosTransType pos_trans_type;
    ClearingBusinessDate clearing_business_date;
    ContraryInstructionIndicator contrary_instruction_indicator;
    EnteringTrader entering_trader;
    LongQty long_qty;

    // parse method
    static PositionMaintenanceRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PositionMaintenanceRequestMessage*>(buffer);
    }

    // parse method const
    static const PositionMaintenanceRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PositionMaintenanceRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
