#pragma once

#include "../types/LastMsgSeqNumProcessed.hpp"
#include "../types/TotNumReports.hpp"
#include "../types/SecurityId.hpp"
#include "../types/NoChunks.hpp"
#include "../types/CurrentChunk.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

// SnapshotFullRefreshOrderBook
struct SnapshotFullRefreshOrderBook {

    LastMsgSeqNumProcessed last_msg_seq_num_processed;
    TotNumReports tot_num_reports;
    SecurityId security_id;
    NoChunks no_chunks;
    CurrentChunk current_chunk;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 53;

    // parse method
    static SnapshotFullRefreshOrderBook* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshOrderBook*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshOrderBook* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshOrderBook*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotFullRefreshOrderBook* parse(const SimpleBinaryHeader* header) {
        return reinterpret_cast<const SnapshotFullRefreshOrderBook*>(reinterpret_cast<const std::byte*>(header) + sizeof(SimpleBinaryHeader));
    }
};

#pragma pack(pop)
}
