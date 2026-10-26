#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/TriggeredSide.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/TotalInvalidation.hpp"
#include "../types/LastPrice.hpp"
#include "../types/MatchId.hpp"
#include "../types/BestOffer.hpp"
#include "../types/BestBid.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides summary information about execution. Delivered when an execution occurs.
struct ExecutionSummaryMessage {

    TimeMicroseconds time_microseconds;
    TriggeredSide triggered_side;
    TotalVolume total_volume;
    TotalInvalidation total_invalidation;
    LastPrice last_price;
    MatchId match_id;
    BestOffer best_offer;
    BestBid best_bid;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'K';

    // parse method
    static ExecutionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionSummaryMessage*>(buffer);
    }

    // parse method const
    static const ExecutionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExecutionSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
