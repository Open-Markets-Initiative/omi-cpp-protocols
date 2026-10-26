#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Underlying.hpp"
#include "../types/WidthType.hpp"
#include "../types/Multiplier.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// Options Only. The Width Update message is used to communicate opening quote width multiplier. This message will be sent in the event that the exchange decides to change the quote width multiplier on a per underlying basis. For complete details on the opening collars see the US Options Opening Process Specification.
struct WidthUpdateMessage {

    TimeOffset time_offset;
    Underlying underlying;
    WidthType width_type;
    Multiplier multiplier;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xD2;

    // parse method
    static WidthUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<WidthUpdateMessage*>(buffer);
    }

    // parse method const
    static const WidthUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const WidthUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const WidthUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const WidthUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
