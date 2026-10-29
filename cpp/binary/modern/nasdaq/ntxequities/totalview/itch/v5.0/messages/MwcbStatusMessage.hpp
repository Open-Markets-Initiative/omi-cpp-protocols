#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BreachedLevel.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

#pragma pack(push, 1)

// Informs data recipients when a MWCB has breached one of the established levels
struct MwcbStatusMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    BreachedLevel breached_level;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'W';

    // parse method
    static MwcbStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MwcbStatusMessage*>(buffer);
    }

    // parse method const
    static const MwcbStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MwcbStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MwcbStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MwcbStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
