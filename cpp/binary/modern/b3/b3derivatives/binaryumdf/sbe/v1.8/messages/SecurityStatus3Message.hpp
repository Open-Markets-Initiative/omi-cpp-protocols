#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset14Padding2.hpp"
#include "../types/TradSesOpenTime.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

// SecurityStatus_3Message
struct SecurityStatus3Message {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    TradingSessionId trading_session_id;
    SecurityTradingStatus security_trading_status;
    SecurityTradingEvent security_trading_event;
    TradeDate trade_date;
    Offset14Padding2 offset_14_padding_2;
    TradSesOpenTime trad_ses_open_time;
    TransactTime transact_time;
    RptSeq rpt_seq;

    // parse method
    static SecurityStatus3Message* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityStatus3Message*>(buffer);
    }

    // parse method const
    static const SecurityStatus3Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityStatus3Message*>(buffer);
    }
};

#pragma pack(pop)
}
