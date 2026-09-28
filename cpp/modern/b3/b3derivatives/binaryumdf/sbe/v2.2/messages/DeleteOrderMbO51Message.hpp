#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding5.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

#pragma pack(push, 1)

// DeleteOrder_MBO_51Message
struct DeleteOrderMbO51Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding1 offset_9_padding_1;
    MdEntryType md_entry_type;
    Offset11Padding5 offset_11_padding_5;
    MdEntrySizeQuantity md_entry_size_quantity;
    SecondaryOrderId secondary_order_id;
    TransactTime transact_time;
    RptSeq rpt_seq;
    MdCorporateOffsetPriceOptional md_corporate_offset_price_optional;

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
