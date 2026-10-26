#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/SymbolStatus.hpp"
#include "../types/Isin.hpp"
#include "../types/Sedol.hpp"
#include "../types/Segment.hpp"
#include "../types/Underlying.hpp"
#include "../types/Currency.hpp"
#include "../types/ReservedByte.hpp"
#include "../types/Reserved4.hpp"
#include "../types/PreviousClosePrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Used to disseminate information (symbol, segment, ISIN, underlying, etc.) on each instrument
struct SymbolDirectoryMessage {

    Nanosecond nanosecond;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    SymbolStatus symbol_status;
    Isin isin;
    Sedol sedol;
    Segment segment;
    Underlying underlying;
    Currency currency;
    ReservedByte reserved_byte;
    Reserved4 reserved_4;
    PreviousClosePrice previous_close_price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x52;

    // parse method
    static SymbolDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolDirectoryMessage*>(buffer);
    }

    // parse method const
    static const SymbolDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
