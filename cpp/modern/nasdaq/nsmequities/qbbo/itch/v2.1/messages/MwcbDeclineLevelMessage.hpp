#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Level1.hpp"
#include "../types/Level2.hpp"
#include "../types/Level3.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// Informs data recipients what the daily MWCB breach points are set to for the current trading day.
struct MwcbDeclineLevelMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
    Level1 level_1;
    Level2 level_2;
    Level3 level_3;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'V';

    // parse method
    static MwcbDeclineLevelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MwcbDeclineLevelMessage*>(buffer);
    }

    // parse method const
    static const MwcbDeclineLevelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MwcbDeclineLevelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MwcbDeclineLevelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MwcbDeclineLevelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
