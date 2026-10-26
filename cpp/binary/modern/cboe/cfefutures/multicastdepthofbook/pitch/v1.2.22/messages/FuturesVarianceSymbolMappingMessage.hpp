#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/UnitTimestamp.hpp"
#include "../types/FeedSymbol.hpp"
#include "../types/FuturesSymbol.hpp"
#include "../types/AccruedDayVariance.hpp"
#include "../types/NumFinalReturns.hpp"
#include "../types/NumElapsedReturns.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Futures Variance Symbol Mapping message is used to disseminate symbol reference data for S&P 500 Variance Futures (VA Futures) symbols.
struct FuturesVarianceSymbolMappingMessage {

    TimeOffset time_offset;
    UnitTimestamp unit_timestamp;
    FeedSymbol feed_symbol;
    FuturesSymbol futures_symbol;
    AccruedDayVariance accrued_day_variance;
    NumFinalReturns num_final_returns;
    NumElapsedReturns num_elapsed_returns;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xFA;

    // parse method
    static FuturesVarianceSymbolMappingMessage* parse(std::byte* buffer) {
        return reinterpret_cast<FuturesVarianceSymbolMappingMessage*>(buffer);
    }

    // parse method const
    static const FuturesVarianceSymbolMappingMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const FuturesVarianceSymbolMappingMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const FuturesVarianceSymbolMappingMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const FuturesVarianceSymbolMappingMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
