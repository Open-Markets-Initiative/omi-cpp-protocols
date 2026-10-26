#pragma once

#include "../types/FeedSymbol.hpp"
#include "../types/OsiSymbol.hpp"
#include "../types/SymbolCondition.hpp"
#include "../types/Underlying.hpp"
#include "../types/SoqIdentifier.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// C1 Only. The Constituent Symbol Mapping message is only available on the C1 Exchange. This message is used to communicate which options series (if any) are Constituent Series in a Volatility Settlement Special Opening Quote (SOQ). The message is identical to the Symbol Mapping message with the addition of the SOQ Identifier field, which is set to the CSMi symbol on which the final settlement SOQ value is disseminated. The Constituent Symbol Mapping message is sent as an unsequenced message with one message sent for each Constituent Series in a continuous loop as bandwidth allows.
struct ConstituentSymbolMappingMessage {

    FeedSymbol feed_symbol;
    OsiSymbol osi_symbol;
    SymbolCondition symbol_condition;
    Underlying underlying;
    SoqIdentifier soq_identifier;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x9E;

    // parse method
    static ConstituentSymbolMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ConstituentSymbolMappingMessage*>(buffer);
    }

    // parse method const
    static const ConstituentSymbolMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ConstituentSymbolMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ConstituentSymbolMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ConstituentSymbolMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
