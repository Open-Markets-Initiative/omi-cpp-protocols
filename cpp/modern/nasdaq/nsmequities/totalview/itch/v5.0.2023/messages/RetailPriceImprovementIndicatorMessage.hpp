#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/InterestFlag.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Identifies a retail interest indication of the Bid, Ask or both the Bid and Ask for NASDAQ-listed securities.
struct RetailPriceImprovementIndicatorMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    InterestFlag interest_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'N';

    // parse method
    static RetailPriceImprovementIndicatorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetailPriceImprovementIndicatorMessage*>(buffer);
    }

    // parse method const
    static const RetailPriceImprovementIndicatorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetailPriceImprovementIndicatorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetailPriceImprovementIndicatorMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const RetailPriceImprovementIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
