#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/NavOffsetAmountHigh.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/NavOffsetAmountLow.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/NavOffsetAmountClosing.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPrice.hpp"
#include "../types/NavOffsetAmountOpen.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// Summarises the consolidated trading activity for a NextShares issue, each price paired with the Nav offset to apply to it.
struct NextSharesEndOfDayTradeSummaryMessage {

    IssueSymbol issue_symbol;
    MarketCategory market_category;
    ConsolidatedHighPrice consolidated_high_price;
    NavOffsetAmountHigh nav_offset_amount_high;
    ConsolidatedLowPrice consolidated_low_price;
    NavOffsetAmountLow nav_offset_amount_low;
    ConsolidatedClosingPrice consolidated_closing_price;
    NavOffsetAmountClosing nav_offset_amount_closing;
    ConsolidatedVolume consolidated_volume;
    ConsolidatedOpenPrice consolidated_open_price;
    NavOffsetAmountOpen nav_offset_amount_open;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'N';

    // parse method
    static NextSharesEndOfDayTradeSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NextSharesEndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse method const
    static const NextSharesEndOfDayTradeSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NextSharesEndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NextSharesEndOfDayTradeSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NextSharesEndOfDayTradeSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
