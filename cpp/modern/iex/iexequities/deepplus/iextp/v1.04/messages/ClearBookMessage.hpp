#pragma once

#include "../types/Reserved1.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

#pragma pack(push, 1)

// This message is used to indicate that the IEX Book for a symbol has been cleared of all orders
struct ClearBookMessage {

    Reserved1 reserved_1;
    Timestamp timestamp;
    Symbol symbol;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static ClearBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ClearBookMessage*>(buffer);
    }

    // parse method const
    static const ClearBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClearBookMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ClearBookMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ClearBookMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
