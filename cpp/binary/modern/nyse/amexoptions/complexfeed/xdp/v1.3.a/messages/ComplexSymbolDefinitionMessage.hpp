#pragma once

#include "../types/ComplexIndex.hpp"
#include "../types/ComplexSymbol.hpp"
#include "../types/ChannelId.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/Reserved1.hpp"
#include "../types/StreamId.hpp"
#include "../types/NoOfLegs.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Complex Symbol Definition message provides a description of the legs in a Complex symbol, and specifies its Complex symbol ID, which is unique for its stream. If the same symbol ID appears in a different stream, it represents a different Complex symbol.
struct ComplexSymbolDefinitionMessage {

    ComplexIndex complex_index;
    ComplexSymbol complex_symbol;
    ChannelId channel_id;
    MarketId market_id;
    SystemId system_id;
    Reserved1 reserved_1;
    StreamId stream_id;
    NoOfLegs no_of_legs;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 439;

    // parse method
    static ComplexSymbolDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ComplexSymbolDefinitionMessage*>(buffer);
    }

    // parse method const
    static const ComplexSymbolDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ComplexSymbolDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ComplexSymbolDefinitionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ComplexSymbolDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
