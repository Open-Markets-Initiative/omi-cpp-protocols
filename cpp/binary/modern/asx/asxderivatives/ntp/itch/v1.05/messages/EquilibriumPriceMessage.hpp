#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/MatchedQuantity.hpp"
#include "../types/BidQuantity.hpp"
#include "../types/AskQuantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is disseminated in response to changes in the equilibrium price for an order book during a pre-open period
struct EquilibriumPriceMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    EquilibriumPrice equilibrium_price;
    MatchedQuantity matched_quantity;
    BidQuantity bid_quantity;
    AskQuantity ask_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Z';

    // parse method
    static EquilibriumPriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EquilibriumPriceMessage*>(buffer);
    }

    // parse method const
    static const EquilibriumPriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EquilibriumPriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EquilibriumPriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EquilibriumPriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
