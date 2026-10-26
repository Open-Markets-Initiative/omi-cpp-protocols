#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/TradingStatus.hpp"
#include "../bitfields/SymbolStatusFlags.hpp"
#include "../types/Reason.hpp"
#include "../types/SessionChangeReason.hpp"
#include "../types/NewEndTime.hpp"
#include "../types/BookType.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Indicates the trading session (pre-opening, regular trading, etc.) that currently applies to an instrument.
struct SymbolStatusMessage {

    Nanosecond nanosecond;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    TradingStatus trading_status;
    SymbolStatusFlags symbol_status_flags;
    Reason reason;
    SessionChangeReason session_change_reason;
    NewEndTime new_end_time;
    BookType book_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x48;

    // parse method
    static SymbolStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolStatusMessage*>(buffer);
    }

    // parse method const
    static const SymbolStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
