#pragma once

#include "../structs/InboundBusinessHeader.hpp"
#include "../types/PosReqId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrigPosReqRefId.hpp"
#include "../types/PosMaintRptRefId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// PositionMaintenanceCancelRequestMessage
struct PositionMaintenanceCancelRequestMessage {

    InboundBusinessHeader inbound_business_header;
    PosReqId pos_req_id;
    SecurityId security_id;
    OrigPosReqRefId orig_pos_req_ref_id;
    PosMaintRptRefId pos_maint_rpt_ref_id;
    SenderLocation sender_location;
    EnteringTrader entering_trader;

    // parse method
    static PositionMaintenanceCancelRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PositionMaintenanceCancelRequestMessage*>(buffer);
    }

    // parse method const
    static const PositionMaintenanceCancelRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PositionMaintenanceCancelRequestMessage*>(buffer);
    }
};

#pragma pack(pop)
}
