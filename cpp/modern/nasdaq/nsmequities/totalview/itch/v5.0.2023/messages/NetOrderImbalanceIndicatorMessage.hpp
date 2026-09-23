#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/Stock.hpp"
#include "../types/FarPrice.hpp"
#include "../types/NearPrice.hpp"
#include "../types/CurrentReferencePrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceVariationIndicator.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// NASDAQ disseminates NOII data
struct NetOrderImbalanceIndicatorMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
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
    static const NetOrderImbalanceIndicatorMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const NetOrderImbalanceIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
