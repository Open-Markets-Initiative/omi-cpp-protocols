#pragma once

#include "../types/Seconds.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate the "seconds" part of the timestamp that is applicable to all messages that are sent in the current second.
struct SystemTimeMessage {

    Seconds seconds;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = '1';

    // parse method
    static SystemTimeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemTimeMessage*>(buffer);
    }

    // parse method const
    static const SystemTimeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemTimeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemTimeMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SystemTimeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
