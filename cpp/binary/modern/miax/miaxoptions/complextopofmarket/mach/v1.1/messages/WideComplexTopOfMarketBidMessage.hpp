#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/WidePrice.hpp"
#include "../types/WideSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/TopOfMarketQuoteCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate MIAX Complex Top of Market for strategies with high net price or large aggregate MIAX Best Bid or Offer (MBBO) size.
struct WideComplexTopOfMarketBidMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    WidePrice wide_price;
    WideSize wide_size;
    Reserved4 reserved_4;
    TopOfMarketQuoteCondition top_of_market_quote_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'e';

    // parse method
    static WideComplexTopOfMarketBidMessage* parse(std::byte* buffer) {
        return reinterpret_cast<WideComplexTopOfMarketBidMessage*>(buffer);
    }

    // parse method const
    static const WideComplexTopOfMarketBidMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const WideComplexTopOfMarketBidMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const WideComplexTopOfMarketBidMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const WideComplexTopOfMarketBidMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
