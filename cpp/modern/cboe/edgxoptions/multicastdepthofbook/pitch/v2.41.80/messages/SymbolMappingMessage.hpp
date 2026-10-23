#pragma once

#include "../types/FeedSymbol.hpp"
#include "../types/OsiSymbol.hpp"
#include "../types/SymbolCondition.hpp"
#include "../types/Underlying.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// Options Only. A Symbol Mapping message is used to map the 6 character multicast feed symbol field to an OSI symbol and Underlying. These messages are not sequenced (sequence = 0) and are sent continuously through the day at variable rates as bandwidth allows. Members who consume the 5 Gig or 8 Gig-Shaped Multicast PITCH feeds will be able to receive the full list of symbols in approximately 5 minutes.
struct SymbolMappingMessage {

    FeedSymbol feed_symbol;
    OsiSymbol osi_symbol;
    SymbolCondition symbol_condition;
    Underlying underlying;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2E;

    // parse method
    static SymbolMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolMappingMessage*>(buffer);
    }

    // parse method const
    static const SymbolMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
