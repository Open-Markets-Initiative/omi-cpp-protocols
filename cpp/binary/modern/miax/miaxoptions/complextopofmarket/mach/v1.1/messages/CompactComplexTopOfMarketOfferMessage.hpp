#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/CompactPrice.hpp"
#include "../types/CompactSize.hpp"
#include "../types/Reserved2.hpp"
#include "../types/TopOfMarketQuoteCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate each side of the MIAX Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size
struct CompactComplexTopOfMarketOfferMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    CompactPrice compact_price;
    CompactSize compact_size;
    Reserved2 reserved_2;
    TopOfMarketQuoteCondition top_of_market_quote_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'o';

    // parse method
    static CompactComplexTopOfMarketOfferMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CompactComplexTopOfMarketOfferMessage*>(buffer);
    }

    // parse method const
    static const CompactComplexTopOfMarketOfferMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CompactComplexTopOfMarketOfferMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CompactComplexTopOfMarketOfferMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const CompactComplexTopOfMarketOfferMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
