#pragma once

#include "../types/ParticipantId.hpp"
#include "../types/MessageCategory.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct MessageHeader {

    ParticipantId participant_id;
    MessageCategory message_category;

    // parse method
    static MessageHeader* parse(std::byte* buffer) {
        return reinterpret_cast<MessageHeader*>(buffer);
    }

    // parse method const
    static const MessageHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageHeader*>(buffer);
    }
};

#pragma pack(pop)
}
