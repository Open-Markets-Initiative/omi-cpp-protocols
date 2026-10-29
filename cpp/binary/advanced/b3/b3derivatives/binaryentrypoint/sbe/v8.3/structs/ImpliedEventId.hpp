#pragma once

#include <cstddef>
#include "../types/EventId.hpp"
#include "../types/NoRelatedTrades.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

#pragma pack(push, 1)

struct implied_event_id {

    sbe_binaryentrypoint::event_id event_id;
    sbe_binaryentrypoint::no_related_trades no_related_trades;

    // parse method
    static implied_event_id* parse(std::byte* buffer) {
        return reinterpret_cast<implied_event_id*>(buffer);
    }

    // parse method const
    static const implied_event_id* parse(const std::byte* buffer) {
        return reinterpret_cast<const implied_event_id*>(buffer);
    }
};

// layout verification
static_assert(offsetof(implied_event_id, event_id) == 0, "unexpected offset of implied_event_id::event_id");
static_assert(offsetof(implied_event_id, no_related_trades) == 4, "unexpected offset of implied_event_id::no_related_trades");
static_assert(sizeof(implied_event_id) == 6, "unexpected sizeof implied_event_id");

#pragma pack(pop)
}
