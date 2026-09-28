#pragma once

#include "../types/SecurityId.hpp"
#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/TotNumBids.hpp"
#include "../types/TotNumOffers.hpp"
#include "../types/TotNumStats.hpp"
#include "../types/Offset26Padding2.hpp"
#include "../types/LastRptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

#pragma pack(push, 1)

// SnapshotFullRefresh_Header_30Message
struct SnapshotFullRefreshHeader30Message {

    SecurityId security_id;
    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    TotNumReports tot_num_reports;
    TotNumBids tot_num_bids;
    TotNumOffers tot_num_offers;
    TotNumStats tot_num_stats;
    Offset26Padding2 offset_26_padding_2;
    LastRptSeq last_rpt_seq;

    // parse method
    static SnapshotFullRefreshHeader30Message* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshHeader30Message*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshHeader30Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshHeader30Message*>(buffer);
    }
};

#pragma pack(pop)
}
