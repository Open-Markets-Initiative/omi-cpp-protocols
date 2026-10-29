#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/CompactPrice.hpp"
#include "../types/CompactSize.hpp"
#include "../types/TopOfMarketQuoteCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate each side of the MIAX Complex Top of Market for options with low Net Price and small aggregate MIAX Best Bid or Offer (MBBO) size
struct CompactComplexTopOfMarketBidMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    CompactPrice compact_price;
    CompactSize compact_size;
    TopOfMarketQuoteCondition top_of_market_quote_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'b';

    // parse method
    static CompactComplexTopOfMarketBidMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CompactComplexTopOfMarketBidMessage*>(buffer);
    }

    // parse method const
    static const CompactComplexTopOfMarketBidMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CompactComplexTopOfMarketBidMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CompactComplexTopOfMarketBidMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const CompactComplexTopOfMarketBidMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
