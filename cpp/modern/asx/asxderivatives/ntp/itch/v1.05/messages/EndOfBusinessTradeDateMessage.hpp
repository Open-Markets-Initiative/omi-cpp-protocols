#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/EventCode.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message will be sent as the last message for a Business Trade Date to signal no further messages will be disseminated for that date.
struct EndOfBusinessTradeDateMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    EventCode event_code;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

    // parse method
    static EndOfBusinessTradeDateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfBusinessTradeDateMessage*>(buffer);
    }

    // parse method const
    static const EndOfBusinessTradeDateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfBusinessTradeDateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfBusinessTradeDateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfBusinessTradeDateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
