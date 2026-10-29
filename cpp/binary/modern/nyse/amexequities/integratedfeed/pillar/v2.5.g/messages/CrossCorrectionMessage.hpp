#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Volume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// In the event that an earlier Cross Trade has been reported in error, a Cross Correction message is sent.
struct CrossCorrectionMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    CrossId cross_id;
    Volume volume;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 113;

    // parse method
    static CrossCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CrossCorrectionMessage*>(buffer);
    }

    // parse method const
    static const CrossCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossCorrectionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CrossCorrectionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CrossCorrectionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
