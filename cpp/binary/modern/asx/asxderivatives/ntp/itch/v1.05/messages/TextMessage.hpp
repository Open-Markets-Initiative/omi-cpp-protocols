#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/SourceId.hpp"
#include "../types/Text.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message disseminates free text information describing ad-hoc market events
struct TextMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    SourceId source_id;
    Text text;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'x';

    // parse method
    static TextMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TextMessage*>(buffer);
    }

    // parse method const
    static const TextMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TextMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TextMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TextMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
