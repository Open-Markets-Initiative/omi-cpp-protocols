#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/OpenState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// NASDAQ plans to disseminate the Option Open Message for each option as soon as the opening is completed. Upon receipt of the open state message, firms should be advised that the option denoted in the message is now available for auto execution within the NASDAQ Options Market System. Upon receipt of the closed state message, firms should be advised that the option is no longer eligible for auto-execution within the NASDAQ Options Market System.
struct SecurityOpenMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OptionId option_id;
    OpenState open_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static SecurityOpenMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityOpenMessage*>(buffer);
    }

    // parse method const
    static const SecurityOpenMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityOpenMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityOpenMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityOpenMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
