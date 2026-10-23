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
#include "../structs/BundleLeg.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// The Bundles Symbol Directory is a specialised reference data message used for defining combinations with legs greater than 6, specifically Bundle products with legs of 8, 12, 16 or 20 legs
struct BundlesSymbolDirectory {

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
    BundleLeg bundle_leg[20];

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'm';

    // parse method
    static BundlesSymbolDirectory* parse(std::byte* buffer) {
        return reinterpret_cast<BundlesSymbolDirectory*>(buffer);
    }

    // parse method const
    static const BundlesSymbolDirectory* parse(const std::byte* buffer) {
        return reinterpret_cast<const BundlesSymbolDirectory*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BundlesSymbolDirectory* parse(const MessageHeader* header) {
        return reinterpret_cast<const BundlesSymbolDirectory*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
