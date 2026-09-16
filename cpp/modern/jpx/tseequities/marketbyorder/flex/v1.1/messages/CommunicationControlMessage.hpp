#pragma once

#include "../types/TestModeFlag.hpp"
#include "../types/CommunicationStartEndFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about communication control. Delivered when communication starts and ends, and in between at minute intervals.
struct CommunicationControlMessage {

    TestModeFlag test_mode_flag;
    CommunicationStartEndFlag communication_start_end_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static CommunicationControlMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CommunicationControlMessage*>(buffer);
    }

    // parse method const
    static const CommunicationControlMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CommunicationControlMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CommunicationControlMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CommunicationControlMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
