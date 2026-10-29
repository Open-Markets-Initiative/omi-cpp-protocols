#pragma once

#include "../types/Id.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SourceTime.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

#pragma pack(push, 1)

// This message is sent at the start of every second during periods of active data publication.
struct SourceTimeReferenceMessage {

    Id id;
    SymbolSeqNum symbol_seq_num;
    SourceTime source_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 2;

    // parse method
    static SourceTimeReferenceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SourceTimeReferenceMessage*>(buffer);
    }

    // parse method const
    static const SourceTimeReferenceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SourceTimeReferenceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SourceTimeReferenceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SourceTimeReferenceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
