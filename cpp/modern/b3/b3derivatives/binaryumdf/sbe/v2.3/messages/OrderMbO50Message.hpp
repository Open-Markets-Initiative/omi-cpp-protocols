#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/Offset28Padding4.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/MdInsertTimestamp.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MdEntryPrevSize.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// Order_MBO_50Message
struct OrderMbO50Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    MdUpdateAction md_update_action;
    MdEntryType md_entry_type;
    Offset11Padding1 offset_11_padding_1;
    MdCorporateOffsetPriceOptional md_corporate_offset_price_optional;
    MdEntrySizeQuantity md_entry_size_quantity;
    Offset28Padding4 offset_28_padding_4;
    EnteringFirm entering_firm;
    MdInsertTimestamp md_insert_timestamp;
    SecondaryOrderId secondary_order_id;
    RptSeq rpt_seq;
    TransactTime transact_time;
    MdEntryPrevSize md_entry_prev_size;

    // parse method
    static OrderMbO50Message* parse(std::byte* buffer) {
        return reinterpret_cast<OrderMbO50Message*>(buffer);
    }

    // parse method const
    static const OrderMbO50Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderMbO50Message*>(buffer);
    }
};

#pragma pack(pop)
}
