// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: messages/RecapUpdateMessage.hpp
#pragma once

#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PriceType.hpp"
#include "../structs/PrevClosePx.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/NoEntries.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

// The Recap Update message contains the latest Last Sale price, Last Sale size, Total Volume, Open price, High price, Low price, and Previous close price. It is sent as a result of a trade or cancel.
struct RecapUpdateMessage {

    ClassKey class_key;
    SecurityId security_id;
    PriceType price_type;
    PrevClosePx prev_close_px;
    TradeVolume trade_volume;
    NoEntries no_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 21;

    // parse method
    static RecapUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RecapUpdateMessage*>(buffer);
    }

    // parse method const
    static const RecapUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RecapUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RecapUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RecapUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
