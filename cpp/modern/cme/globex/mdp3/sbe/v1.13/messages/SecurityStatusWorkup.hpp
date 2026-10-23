#pragma once

#include "../types/TransactTime.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeLinkId.hpp"
#include "../types/WorkupTradingStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

// SecurityStatusWorkup
struct SecurityStatusWorkup {

    TransactTime transact_time;
    MdEntryPxOptionalEx md_entry_px_optional_ex;
    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradeDate trade_date;
    TradeLinkId trade_link_id;
    WorkupTradingStatus workup_trading_status;
    HaltReason halt_reason;
    SecurityTradingEvent security_trading_event;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 60;

    // parse method
    static SecurityStatusWorkup* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatusWorkup*>(buffer);
    }

    // parse method const
    static const SecurityStatusWorkup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatusWorkup*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityStatusWorkup* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityStatusWorkup*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
