#pragma once

#include "../types/SecurityId.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/TotNoOrders.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/NoMdEntries.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct InstrumentSummary {

    SecurityId security_id;
    LastUpdateTime last_update_time;
    TrdRegTsExecutionTime trd_reg_ts_execution_time;
    TotNoOrders tot_no_orders;
    SecurityStatus security_status;
    SecurityTradingStatus security_trading_status;
    MarketCondition market_condition;
    FastMarketIndicator fast_market_indicator;
    SecurityTradingEvent security_trading_event;
    NoMdEntries no_md_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13601;

    // parse method
    static InstrumentSummary* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentSummary*>(buffer);
    }

    // parse method const
    static const InstrumentSummary* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentSummary*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentSummary* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const InstrumentSummary*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
