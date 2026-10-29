#pragma once

#include "../types/Level1.hpp"
#include "../types/Level2.hpp"
#include "../types/Level3.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Informs the market of the daily market wide circuit breaker decline levels, disseminated at the start of the trading day.
struct MwcbDeclineLevelMessage {

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
