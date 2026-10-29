#pragma once

#include "../types/SecurityId.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/TotNoOrders.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/NoOfTrades.hpp"
#include "../types/Pad4.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published for each instrument in one snapshot cycle, carrying instrument state information and trade statistics.
struct InstrumentSummaryMessage {

    SecurityId security_id;
    LastUpdateTime last_update_time;
    TrdRegTsExecutionTime trd_reg_ts_execution_time;
    TotNoOrders tot_no_orders;
    SecurityStatus security_status;
    SecurityTradingStatus security_trading_status;
    FastMarketIndicator fast_market_indicator;
    NoMdEntries no_md_entries;
    TradeVolume trade_volume;
    NoOfTrades no_of_trades;
    Pad4 pad_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13601;

    // parse method
    static InstrumentSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentSummaryMessage*>(buffer);
    }

    // parse method const
    static const InstrumentSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InstrumentSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
