// Databento.MarketData.Normalized.Dbn.v2: messages/StatusMsg.hpp
#pragma once

#include "../types/TsRecv.hpp"
#include "../types/StatusAction.hpp"
#include "../types/StatusReason.hpp"
#include "../types/TradingEvent.hpp"
#include "../types/IsTrading.hpp"
#include "../types/IsQuoting.hpp"
#include "../types/IsShortSellRestricted.hpp"
#include "../types/Reserved7.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

#pragma pack(push, 1)

// A trading status update message; the record of the status schema
struct StatusMsg {

    TsRecv ts_recv;
    StatusAction status_action;
    StatusReason status_reason;
    TradingEvent trading_event;
    IsTrading is_trading;
    IsQuoting is_quoting;
    IsShortSellRestricted is_short_sell_restricted;
    Reserved7 reserved_7;

    // parse method
    static StatusMsg* parse(std::byte* buffer) {
        return reinterpret_cast<StatusMsg*>(buffer);
    }

    // parse method const
    static const StatusMsg* parse(const std::byte* buffer) {
        return reinterpret_cast<const StatusMsg*>(buffer);
    }
};

#pragma pack(pop)
}
