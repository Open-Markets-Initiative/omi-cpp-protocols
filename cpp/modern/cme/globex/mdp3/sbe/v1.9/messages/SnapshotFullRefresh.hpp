#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/HighLimitPriceEx.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/MaxPriceVariationEx.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

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
    HighLimitPriceEx high_limit_price_ex;
    LowLimitPriceEx low_limit_price_ex;
    MaxPriceVariationEx max_price_variation_ex;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 52;

    // parse method
    static SnapshotFullRefresh* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefresh*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefresh* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefresh*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotFullRefresh* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotFullRefresh*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
