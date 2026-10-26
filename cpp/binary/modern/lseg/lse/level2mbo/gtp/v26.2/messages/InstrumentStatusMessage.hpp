#pragma once

#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/SessionChangeReason.hpp"
#include "../types/NewEndTime.hpp"
#include "../types/OrderBookType.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Used to communicate scheduled and unscheduled session changes. When sent in the recovery channel, used to indicate the current trading status of an instrument.
struct InstrumentStatusMessage {

    Timestamp timestamp;
    Instrument instrument;
    SourceVenue source_venue;
    TradingStatus trading_status;
    SessionChangeReason session_change_reason;
    NewEndTime new_end_time;
    OrderBookType order_book_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x48;

    // parse method
    static InstrumentStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentStatusMessage*>(buffer);
    }

    // parse method const
    static const InstrumentStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InstrumentStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
