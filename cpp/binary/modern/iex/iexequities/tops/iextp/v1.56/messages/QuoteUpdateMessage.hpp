#pragma once

#include "../bitfields/QuoteUpdateFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidPrice.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

#pragma pack(push, 1)

// Tops broadcasts a real-time Quote Update Message each time IEX's best bid or offer quotation is updated during the trading day
struct QuoteUpdateMessage {

    QuoteUpdateFlags quote_update_flags;
    Timestamp timestamp;
    Symbol symbol;
    BidSize bid_size;
    BidPrice bid_price;
    AskPrice ask_price;
    AskSize ask_size;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static QuoteUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteUpdateMessage*>(buffer);
    }

    // parse method const
    static const QuoteUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
