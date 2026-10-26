#pragma once

#include "../types/MidnightReference.hpp"
#include "../types/TimeReference.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/TradeDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Time Reference message is used to provide a midnight reference point for recipients of the feed. It is sent whenever the system starts up and when the system crosses a midnight boundary.
struct TimeReferenceMessage {

    MidnightReference midnight_reference;
    TimeReference time_reference;
    TimeOffset time_offset;
    TradeDate trade_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xB1;

    // parse method
    static TimeReferenceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TimeReferenceMessage*>(buffer);
    }

    // parse method const
    static const TimeReferenceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TimeReferenceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TimeReferenceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TimeReferenceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
