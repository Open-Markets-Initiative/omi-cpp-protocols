#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/RpiIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// Published when RPI interest is added or removed between the best bid and best offer price.
struct RetailPriceImprovementMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    RpiIndicator rpi_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 114;

    // parse method
    static RetailPriceImprovementMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetailPriceImprovementMessage*>(buffer);
    }

    // parse method const
    static const RetailPriceImprovementMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetailPriceImprovementMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetailPriceImprovementMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RetailPriceImprovementMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
