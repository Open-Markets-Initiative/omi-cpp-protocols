#pragma once

#include "../types/SecurityGroup.hpp"
#include "../types/Offset3Padding5.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset14Padding2.hpp"
#include "../types/TradSesOpenTime.hpp"
#include "../types/TransactTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

// SecurityGroupPhase_10Message
struct SecurityGroupPhase10Message {

    SecurityGroup security_group;
    Offset3Padding5 offset_3_padding_5;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    SecurityTradingEvent security_trading_event;
    TradeDate trade_date;
    Offset14Padding2 offset_14_padding_2;
    TradSesOpenTime trad_ses_open_time;
    TransactTime transact_time;

    // parse method
    static SecurityGroupPhase10Message* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityGroupPhase10Message*>(buffer);
    }

    // parse method const
    static const SecurityGroupPhase10Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityGroupPhase10Message*>(buffer);
    }
};

#pragma pack(pop)
}
