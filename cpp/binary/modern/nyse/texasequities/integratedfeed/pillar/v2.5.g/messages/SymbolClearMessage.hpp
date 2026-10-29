#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/NextSourceSeqNum.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// In case of a failure and recovery of a Matching Engine or an Pillar Publisher, the publisher may send a full state refresh for every symbol affected. This unrequested refresh is preceded by a Symbol Clear message. The client should react to receipt of a Symbol Clear message by clearing all state information for the specified symbol in anticipation of receiving a full state refresh.
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
