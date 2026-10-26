#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding5.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// MassDeleteOrders_MBO_52Message
struct MassDeleteOrdersMbO52Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    MdEntryType md_entry_type;
    Offset11Padding5 offset_11_padding_5;
    TransactTime transact_time;
    RptSeq rpt_seq;

    // parse method
    static MassDeleteOrdersMbO52Message* parse(std::byte* buffer) {
        return reinterpret_cast<MassDeleteOrdersMbO52Message*>(buffer);
    }

    // parse method const
    static const MassDeleteOrdersMbO52Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const MassDeleteOrdersMbO52Message*>(buffer);
    }
};

#pragma pack(pop)
}
