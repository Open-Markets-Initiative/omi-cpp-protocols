#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published regularly when there is no activity on the snapshot or the incremental channel.
struct HeartbeatMessage {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    Pad4 pad_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13001;

    // parse method
    static HeartbeatMessage* parse(std::byte* buffer) {
        return reinterpret_cast<HeartbeatMessage*>(buffer);
    }

    // parse method const
    static const HeartbeatMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const HeartbeatMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const HeartbeatMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const HeartbeatMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
