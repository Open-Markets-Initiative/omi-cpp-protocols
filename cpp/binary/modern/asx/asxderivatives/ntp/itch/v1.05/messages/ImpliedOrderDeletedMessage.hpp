#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is sent whenever the implied pricing or volume has changed due to price or volume movement of “real” orders for a side of a single contract number. When received, any implied volume is no longer accessible so the “implied” order of the indicated side must be removed from the book
struct ImpliedOrderDeletedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'k';

    // parse method
    static ImpliedOrderDeletedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ImpliedOrderDeletedMessage*>(buffer);
    }

    // parse method const
    static const ImpliedOrderDeletedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImpliedOrderDeletedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ImpliedOrderDeletedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ImpliedOrderDeletedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
