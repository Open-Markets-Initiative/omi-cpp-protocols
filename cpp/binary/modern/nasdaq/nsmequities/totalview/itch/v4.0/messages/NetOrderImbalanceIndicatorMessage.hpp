#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/Stock.hpp"
#include "../types/FarPrice.hpp"
#include "../types/NearPrice.hpp"
#include "../types/CurrentReferencePrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceVariationIndicator.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// NASDAQ disseminates NOII data at 5-second intervals in the minutes leading up to the NASDAQ Opening Cross and NASDAQ Closing Cross.
struct NetOrderImbalanceIndicatorMessage {

    Nanoseconds nanoseconds;
    PairedShares paired_shares;
    ImbalanceShares imbalance_shares;
    ImbalanceDirection imbalance_direction;
    Stock stock;
    FarPrice far_price;
    NearPrice near_price;
    CurrentReferencePrice current_reference_price;
    CrossType cross_type;
    PriceVariationIndicator price_variation_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'I';

    // parse method
    static NetOrderImbalanceIndicatorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NetOrderImbalanceIndicatorMessage*>(buffer);
    }

    // parse method const
    static const NetOrderImbalanceIndicatorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NetOrderImbalanceIndicatorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NetOrderImbalanceIndicatorMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NetOrderImbalanceIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
