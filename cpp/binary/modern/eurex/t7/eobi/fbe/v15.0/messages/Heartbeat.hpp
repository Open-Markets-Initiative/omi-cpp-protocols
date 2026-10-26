#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct Heartbeat {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    Pad4 pad4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13001;

    // parse method
    static Heartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<Heartbeat*>(buffer);
    }

    // parse method const
    static const Heartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const Heartbeat*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const Heartbeat* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const Heartbeat*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
