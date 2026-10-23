#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/RfqSide.hpp"
#include "../types/Quantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is disseminated for anonymous Request for Quotes (RFQs) from the market
struct RequestForQuoteMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    RfqSide rfq_side;
    Quantity quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'q';

    // parse method
    static RequestForQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RequestForQuoteMessage*>(buffer);
    }

    // parse method const
    static const RequestForQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestForQuoteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RequestForQuoteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RequestForQuoteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
