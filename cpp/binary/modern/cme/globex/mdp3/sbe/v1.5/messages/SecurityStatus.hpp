#pragma once

#include "../types/TransactTime.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../types/TradeDate.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

// SecurityStatus
struct SecurityStatus {

    TransactTime transact_time;
    SecurityGroup security_group;
    Asset asset;
    SecurityIdOptional security_id_optional;
    TradeDate trade_date;
    MatchEventIndicator match_event_indicator;
    SecurityTradingStatus security_trading_status;
    HaltReason halt_reason;
    SecurityTradingEvent security_trading_event;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 30;

    // parse method
    static SecurityStatus* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatus*>(buffer);
    }

    // parse method const
    static const SecurityStatus* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatus*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityStatus* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const SecurityStatus*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
