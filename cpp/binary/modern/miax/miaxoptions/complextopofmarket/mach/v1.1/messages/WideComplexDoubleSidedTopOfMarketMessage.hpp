#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../structs/WideBid.hpp"
#include "../structs/WideOffer.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with net prices or aggregate sizes which cannot be specified in the compact format.
struct WideComplexDoubleSidedTopOfMarketMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    WideBid wide_bid;
    WideOffer wide_offer;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'w';

    // parse method
    static WideComplexDoubleSidedTopOfMarketMessage* parse(std::byte* buffer) {
        return reinterpret_cast<WideComplexDoubleSidedTopOfMarketMessage*>(buffer);
    }

    // parse method const
    static const WideComplexDoubleSidedTopOfMarketMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const WideComplexDoubleSidedTopOfMarketMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const WideComplexDoubleSidedTopOfMarketMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const WideComplexDoubleSidedTopOfMarketMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
