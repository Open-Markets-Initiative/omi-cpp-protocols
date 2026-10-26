#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/BreachedLevel.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Informs data recipients when a MWCB has breached one of the established levels
struct MwcbBreachMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
    BreachedLevel breached_level;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'W';

    // parse method
    static MwcbBreachMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MwcbBreachMessage*>(buffer);
    }

    // parse method const
    static const MwcbBreachMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MwcbBreachMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MwcbBreachMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MwcbBreachMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
