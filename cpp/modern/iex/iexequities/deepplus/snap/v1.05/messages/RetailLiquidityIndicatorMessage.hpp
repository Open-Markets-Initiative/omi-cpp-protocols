#pragma once

#include "../types/RetailLiquidityIndicator.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../messages/SnapshotDataMessage.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

#pragma pack(push, 1)

// broadcasts a real-time Retail Liquidity Indicator Message each time there is an update to IEX's eligible retail liquidity interest during the trading day
struct RetailLiquidityIndicatorMessage {

    RetailLiquidityIndicator retail_liquidity_indicator;
    Timestamp timestamp;
    Symbol symbol;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'I';

    // parse method
    static RetailLiquidityIndicatorMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetailLiquidityIndicatorMessage*>(buffer);
    }

    // parse method const
    static const RetailLiquidityIndicatorMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetailLiquidityIndicatorMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetailLiquidityIndicatorMessage* parse(const SnapshotDataMessage* header) {
        return reinterpret_cast<const RetailLiquidityIndicatorMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SnapshotDataMessage));
    }
};

#pragma pack(pop)
}
