#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../structs/CompactBid.hpp"
#include "../structs/CompactOffer.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate both sides of the MIAX top of market for strategies (cMBBO) with low net price and small aggregate size.
struct CompactComplexDoubleSidedTopOfMarketMessage {

    Nanoseconds nanoseconds;
    StrategyId strategy_id;
    CompactBid compact_bid;
    CompactOffer compact_offer;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'm';

    // parse method
    static CompactComplexDoubleSidedTopOfMarketMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CompactComplexDoubleSidedTopOfMarketMessage*>(buffer);
    }

    // parse method const
    static const CompactComplexDoubleSidedTopOfMarketMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CompactComplexDoubleSidedTopOfMarketMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CompactComplexDoubleSidedTopOfMarketMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const CompactComplexDoubleSidedTopOfMarketMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
