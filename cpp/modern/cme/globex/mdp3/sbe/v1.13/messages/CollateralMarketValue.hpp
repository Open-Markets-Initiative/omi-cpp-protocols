#pragma once

#include "../types/TransactTime.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// CollateralMarketValue
struct CollateralMarketValue {

    TransactTime transact_time;
    MatchEventIndicator match_event_indicator;
    Padding2 padding_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 62;

    // parse method
    static CollateralMarketValue* parse(std::byte* buffer) {
        return reinterpret_cast<CollateralMarketValue*>(buffer);
    }

    // parse method const
    static const CollateralMarketValue* parse(const std::byte* buffer) {
        return reinterpret_cast<const CollateralMarketValue*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CollateralMarketValue* parse(const MessageHeader* header) {
        return reinterpret_cast<const CollateralMarketValue*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
