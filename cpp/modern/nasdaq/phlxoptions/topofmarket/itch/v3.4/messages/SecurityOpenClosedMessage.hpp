#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/OpenState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The options system uses this administrative message to indicate when an option has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution.
struct SecurityOpenClosedMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    OpenState open_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static SecurityOpenClosedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityOpenClosedMessage*>(buffer);
    }

    // parse method const
    static const SecurityOpenClosedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityOpenClosedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityOpenClosedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityOpenClosedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
