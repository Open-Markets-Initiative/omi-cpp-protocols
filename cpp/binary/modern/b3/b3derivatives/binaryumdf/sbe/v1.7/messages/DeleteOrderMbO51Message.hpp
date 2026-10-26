#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdEntryPositionNo.hpp"
#include "../types/MdEntrySizeQuantityOptional.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

#pragma pack(push, 1)

// DeleteOrder_MBO_51Message
struct DeleteOrderMbO51Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding1 offset_9_padding_1;
    MdEntryType md_entry_type;
    Offset11Padding1 offset_11_padding_1;
    MdEntryPositionNo md_entry_position_no;
    MdEntrySizeQuantityOptional md_entry_size_quantity_optional;
    SecondaryOrderId secondary_order_id;
    MdEntryTimestamp md_entry_timestamp;
    RptSeq rpt_seq;

    // parse method
    static DeleteOrderMbO51Message* parse(std::byte* buffer) {
        return reinterpret_cast<DeleteOrderMbO51Message*>(buffer);
    }

    // parse method const
    static const DeleteOrderMbO51Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeleteOrderMbO51Message*>(buffer);
    }
};

#pragma pack(pop)
}
