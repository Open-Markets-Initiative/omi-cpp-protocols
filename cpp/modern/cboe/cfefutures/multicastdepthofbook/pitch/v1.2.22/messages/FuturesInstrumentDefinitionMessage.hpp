#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/UnitTimestamp.hpp"
#include "../types/ReportSymbol.hpp"
#include "../bitfields/FuturesFlags.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/ContractSize.hpp"
#include "../types/ListingState.hpp"
#include "../types/PriceIncrement.hpp"
#include "../types/LegCount.hpp"
#include "../types/LegOffset.hpp"
#include "../types/Reserved1.hpp"
#include "../types/ContractDate.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Futures Instrument Definition message can be sent as a sequenced message or an un-sequenced message. It is sent as a sequenced message when the system starts up at the beginning of a trading session or an the instrument is created or modified during a trading day.
struct FuturesInstrumentDefinitionMessage {

    TimeOffset time_offset;
    Symbol symbol;
    UnitTimestamp unit_timestamp;
    ReportSymbol report_symbol;
    FuturesFlags futures_flags;
    ExpirationDate expiration_date;
    ContractSize contract_size;
    ListingState listing_state;
    PriceIncrement price_increment;
    LegCount leg_count;
    LegOffset leg_offset;
    Reserved1 reserved_1;
    ContractDate contract_date;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBB;

    // parse method
    static FuturesInstrumentDefinitionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FuturesInstrumentDefinitionMessage*>(buffer);
    }

    // parse method const
    static const FuturesInstrumentDefinitionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FuturesInstrumentDefinitionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const FuturesInstrumentDefinitionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const FuturesInstrumentDefinitionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
