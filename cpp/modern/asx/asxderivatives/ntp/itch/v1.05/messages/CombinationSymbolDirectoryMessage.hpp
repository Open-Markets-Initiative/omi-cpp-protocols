#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SymbolName.hpp"
#include "../types/LongName.hpp"
#include "../types/CfiCode.hpp"
#include "../types/PriceMethod.hpp"
#include "../types/PriceDisplayDecimals.hpp"
#include "../types/PriceFractionalDenominator.hpp"
#include "../types/PriceMinimumTick.hpp"
#include "../types/Legs.hpp"
#include "../structs/CombinationLeg.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// The Combination Symbol Directory is a specialised reference data message used for defining combinations with up to 6 legs. It represents both standard combinations defined by ASX and user defined combinations created by participants
struct CombinationSymbolDirectoryMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    SymbolName symbol_name;
    LongName long_name;
    CfiCode cfi_code;
    PriceMethod price_method;
    PriceDisplayDecimals price_display_decimals;
    PriceFractionalDenominator price_fractional_denominator;
    PriceMinimumTick price_minimum_tick;
    Legs legs;
    CombinationLeg combination_leg[6];

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'M';

    // parse method
    static CombinationSymbolDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CombinationSymbolDirectoryMessage*>(buffer);
    }

    // parse method const
    static const CombinationSymbolDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CombinationSymbolDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CombinationSymbolDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CombinationSymbolDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
