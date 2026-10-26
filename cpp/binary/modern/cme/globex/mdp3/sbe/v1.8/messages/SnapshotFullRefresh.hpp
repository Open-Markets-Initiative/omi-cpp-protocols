#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// SnapshotFullRefresh
struct SnapshotFullRefresh {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    TotNumReports tot_num_reports;
    SecurityId security_id;
    RptSeq rpt_seq;
    TransactTime transact_time;
    LastUpdateTime last_update_time;
    TradeDate trade_date;
    MdSecurityTradingStatus md_security_trading_status;
    HighLimitPrice high_limit_price;
    LowLimitPrice low_limit_price;
    MaxPriceVariation max_price_variation;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 38;

    // parse method
    static SnapshotFullRefresh* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefresh*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefresh* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefresh*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotFullRefresh* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const SnapshotFullRefresh*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
