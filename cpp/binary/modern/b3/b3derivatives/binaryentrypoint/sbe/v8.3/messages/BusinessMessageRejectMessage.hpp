#pragma once

#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/RefMsgType.hpp"
#include "../types/Offset19Padding1.hpp"
#include "../types/RefSeqNum.hpp"
#include "../types/BusinessRejectRefId.hpp"
#include "../types/BusinessRejectReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

// BusinessMessageRejectMessage
struct BusinessMessageRejectMessage {

    OutboundBusinessHeader outbound_business_header;
    RefMsgType ref_msg_type;
    Offset19Padding1 offset_19_padding_1;
    RefSeqNum ref_seq_num;
    BusinessRejectRefId business_reject_ref_id;
    BusinessRejectReason business_reject_reason;

    // parse method
    static BusinessMessageRejectMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BusinessMessageRejectMessage*>(buffer);
    }

    // parse method const
    static const BusinessMessageRejectMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BusinessMessageRejectMessage*>(buffer);
    }
};

#pragma pack(pop)
}
