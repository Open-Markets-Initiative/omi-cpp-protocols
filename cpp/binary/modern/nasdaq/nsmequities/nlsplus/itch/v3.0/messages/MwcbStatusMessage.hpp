#pragma once

#include "../types/BreachedLevel.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Informs the market that a market wide circuit breaker decline level has been breached.
struct MwcbStatusMessage {

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
