#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/CrossShares.hpp"
#include "../types/Stock.hpp"
#include "../types/CrossPrice.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// Cross Trade message indicates that Nasdaq has completed its cross process for a specific security
struct CrossTradeMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    CrossShares cross_shares;
    Stock stock;
    CrossPrice cross_price;
    MatchNumber match_number;
    CrossType cross_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static CrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CrossTradeMessage*>(buffer);
    }

    // parse method const
    static const CrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CrossTradeMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const CrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
