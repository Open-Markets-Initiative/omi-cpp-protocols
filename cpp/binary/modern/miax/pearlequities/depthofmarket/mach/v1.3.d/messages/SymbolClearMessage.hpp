#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message format is used to indicate that the MIAX Pearl Equities book for a symbol has been cleared of all orders.
struct SymbolClearMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 5;

    // parse method
    static SymbolClearMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolClearMessage*>(buffer);
    }

    // parse method const
    static const SymbolClearMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolClearMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolClearMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SymbolClearMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
