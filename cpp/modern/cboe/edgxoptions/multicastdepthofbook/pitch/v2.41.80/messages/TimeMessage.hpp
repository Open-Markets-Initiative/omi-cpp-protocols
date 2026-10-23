#pragma once

#include "../types/Time.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// A Time message is immediately generated and sent when there is a PITCH event for a given clock second. If there is no PITCH event for a given clock second, then no Time message is sent for that second. The Time field is the number of seconds relative to midnight Eastern Time. All subsequent time offset fields for the same unit will use the new Time message value as the base until another Time message is received for the same unit.
struct TimeMessage {

    Time time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x20;

    // parse method
    static TimeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TimeMessage*>(buffer);
    }

    // parse method const
    static const TimeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TimeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TimeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TimeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
