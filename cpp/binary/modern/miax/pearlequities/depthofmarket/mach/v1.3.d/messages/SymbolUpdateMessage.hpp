#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TickerSymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/TestSecurityIndicator.hpp"
#include "../types/SecondReserved1.hpp"
#include "../types/LotSize.hpp"
#include "../types/OpeningTime.hpp"
#include "../types/ClosingTime.hpp"
#include "../types/PrimaryMarketCode.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate all security symbols traded on MIAX Pearl Equities for the current trading session. The Symbol ID sent in this message will be disseminated in Depth of Market messages.
struct SymbolUpdateMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    TickerSymbol ticker_symbol;
    Reserved1 reserved_1;
    TestSecurityIndicator test_security_indicator;
    SecondReserved1 second_reserved_1;
    LotSize lot_size;
    OpeningTime opening_time;
    ClosingTime closing_time;
    PrimaryMarketCode primary_market_code;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 1;

    // parse method
    static SymbolUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolUpdateMessage*>(buffer);
    }

    // parse method const
    static const SymbolUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolUpdateMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SymbolUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
