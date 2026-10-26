#pragma once

#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/Offset16Padding4.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/MdInsertTimestamp.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/MdEntryType.hpp"
#include "../bitfields/MatchEventIndicator.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

#pragma pack(push, 1)

struct SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup {

    MdCorporateOffsetPriceOptional md_corporate_offset_price_optional;
    MdEntrySizeQuantity md_entry_size_quantity;
    Offset16Padding4 offset_16_padding_4;
    EnteringFirm entering_firm;
    MdInsertTimestamp md_insert_timestamp;
    SecondaryOrderId secondary_order_id;
    MdEntryType md_entry_type;
    MatchEventIndicator match_event_indicator;

    // parse method
    static SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup*>(buffer);
    }
};

#pragma pack(pop)
}
