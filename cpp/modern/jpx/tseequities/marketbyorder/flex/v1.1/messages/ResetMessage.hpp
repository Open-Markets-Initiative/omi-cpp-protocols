#pragma once

#include "../types/ResetStartEndFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// A tag requesting the resetting (i.e. cancellation) of all distributed information. When the user receives this tag, the user must clear all valid A tags.
struct ResetMessage {

    ResetStartEndFlag reset_start_end_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static ResetMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ResetMessage*>(buffer);
    }

    // parse method const
    static const ResetMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ResetMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ResetMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ResetMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
