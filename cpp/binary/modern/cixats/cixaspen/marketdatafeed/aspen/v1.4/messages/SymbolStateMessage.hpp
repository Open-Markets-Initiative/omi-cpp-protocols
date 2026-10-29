#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Symbol.hpp"
#include "../types/State.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Info.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Individual symbol trading state (halts)
struct SymbolStateMessage {

    Timestamp timestamp;
    SymbolId symbol_id;
    Symbol symbol;
    State state;
    Reserved1 reserved_1;
    Info info;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static SymbolStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolStateMessage*>(buffer);
    }

    // parse method const
    static const SymbolStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolStateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
