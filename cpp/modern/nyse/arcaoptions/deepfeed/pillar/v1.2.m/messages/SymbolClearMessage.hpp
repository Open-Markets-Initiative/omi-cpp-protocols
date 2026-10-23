#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/NextSourceSeqNum.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// In case of a failure and recovery, the publisher may send a full state refresh for every symbol or series affected, preceded by a Symbol Clear message.
struct SymbolClearMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    NextSourceSeqNum next_source_seq_num;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 32;

    // parse method
    static SymbolClearMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolClearMessage*>(buffer);
    }

    // parse method const
    static const SymbolClearMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolClearMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolClearMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolClearMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
