#pragma once

#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPriceLong.hpp"
#include "../types/ConsolidatedLowPriceLong.hpp"
#include "../types/ConsolidatedClosingPriceLong.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPriceLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// End of Day Trade Summary carrying eight byte prices.
struct LongFormEndOfDayTradeSummaryMessage {

    IssueSymbol issue_symbol;
    MarketCategory market_category;
    ConsolidatedHighPriceLong consolidated_high_price_long;
    ConsolidatedLowPriceLong consolidated_low_price_long;
    ConsolidatedClosingPriceLong consolidated_closing_price_long;
    ConsolidatedVolume consolidated_volume;
    ConsolidatedOpenPriceLong consolidated_open_price_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'j';

    // parse method
    static LongFormEndOfDayTradeSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongFormEndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse method const
    static const LongFormEndOfDayTradeSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongFormEndOfDayTradeSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const LongFormEndOfDayTradeSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const LongFormEndOfDayTradeSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
