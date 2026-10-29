#pragma once

#include "../types/Timestamp.hpp"
#include "../types/EventCode.hpp"
#include "../types/CurrentYear.hpp"
#include "../types/CurrentMonth.hpp"
#include "../types/CurrentDay.hpp"
#include "../types/Version.hpp"
#include "../types/SubVersion.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

#pragma pack(push, 1)

// The system event message type is used to signal a market or data feed handler event.
struct SystemEventMessage {

    Timestamp timestamp;
    EventCode event_code;
    CurrentYear current_year;
    CurrentMonth current_month;
    CurrentDay current_day;
    Version version;
    SubVersion sub_version;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

    // parse method
    static SystemEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemEventMessage*>(buffer);
    }

    // parse method const
    static const SystemEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SystemEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
