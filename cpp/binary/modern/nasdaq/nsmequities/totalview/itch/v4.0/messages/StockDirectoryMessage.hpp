#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/RoundLotsOnly.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// Market data redistributors should process this message to populate the Financial Status Indicator (required display field) and the Market Category (recommended display field) for NASDAQ-listed issues.
struct StockDirectoryMessage {

    Nanoseconds nanoseconds;
    Stock stock;
    MarketCategory market_category;
    FinancialStatusIndicator financial_status_indicator;
    RoundLotSize round_lot_size;
    RoundLotsOnly round_lots_only;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static StockDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StockDirectoryMessage*>(buffer);
    }

    // parse method const
    static const StockDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StockDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StockDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StockDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
