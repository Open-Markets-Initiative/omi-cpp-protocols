#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/SecurityId.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// SnapshotFullRefreshTCP
struct SnapshotFullRefreshTcp {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    SecurityId security_id;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 61;

    // parse method
    static SnapshotFullRefreshTcp* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshTcp*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshTcp* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshTcp*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotFullRefreshTcp* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotFullRefreshTcp*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
