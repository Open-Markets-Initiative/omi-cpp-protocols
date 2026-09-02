#pragma once

#include "../types/TradingStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reason.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

#pragma pack(push, 1)

// The Trading Status Message is used to indicate the current trading status of a security.
struct TradingStatusMessage {

    TradingStatus trading_status;
    Timestamp timestamp;
    Symbol symbol;
    Reason reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static TradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingStatusMessage*>(buffer);
    }

    // parse method const
    static const TradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
