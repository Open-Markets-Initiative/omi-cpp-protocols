#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/Open.hpp"
#include "../types/Close.hpp"
#include "../types/TotalVolume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

#pragma pack(push, 1)

// On a separate channel from the main feed, the Stock Summary channel, a Stock Summary message per symbol is sent every 60 seconds. The message is sent regardless of whether there has been a change to the symbol in the last 60 seconds or not.
struct StockSummaryMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    HighPrice high_price;
    LowPrice low_price;
    Open open;
    Close close;
    TotalVolume total_volume;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 223;

    // parse method
    static StockSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockSummaryMessage*>(buffer);
    }

    // parse method const
    static const StockSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StockSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StockSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
