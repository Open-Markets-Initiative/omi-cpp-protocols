#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// SnapshotRefreshTopOrders
struct SnapshotRefreshTopOrders {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    SecurityId security_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 59;

    // parse method
    static SnapshotRefreshTopOrders* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotRefreshTopOrders*>(buffer);
    }

    // parse method const
    static const SnapshotRefreshTopOrders* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotRefreshTopOrders*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotRefreshTopOrders* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const SnapshotRefreshTopOrders*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
