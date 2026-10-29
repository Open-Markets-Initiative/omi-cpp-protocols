#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Summarises the consolidated trading activity for an issue at the end of the trading day.
struct EndOfDayTradeSummaryMessage {

    IssueSymbol issue_symbol;
    MarketCategory market_category;
    ConsolidatedHighPrice consolidated_high_price;
    ConsolidatedLowPrice consolidated_low_price;
    ConsolidatedClosingPrice consolidated_closing_price;
    ConsolidatedVolume consolidated_volume;
    ConsolidatedOpenPrice consolidated_open_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static EndOfDayTradeSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse method const
    static const EndOfDayTradeSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfDayTradeSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfDayTradeSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
