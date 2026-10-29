#pragma once

#include "../types/EventId.hpp"
#include "../types/NoRelatedTrades.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

#pragma pack(push, 1)

struct ImpliedEventId {

    EventId event_id;
    NoRelatedTrades no_related_trades;

    // parse method
    static ImpliedEventId* parse(std::byte* buffer) {
        return reinterpret_cast<ImpliedEventId*>(buffer);
    }

    // parse method const
    static const ImpliedEventId* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImpliedEventId*>(buffer);
    }
};

#pragma pack(pop)
}
