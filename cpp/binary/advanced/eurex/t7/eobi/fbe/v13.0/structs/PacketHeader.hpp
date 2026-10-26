#pragma once

#include <cstddef>
#include "../structs/EobiHeader.hpp"
#include "../types/ApplSeqNum.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/PartitionId.hpp"
#include "../types/CompletionIndicator.hpp"
#include "../types/ApplSeqResetIndicator.hpp"
#include "../types/Dscp.hpp"
#include "../types/Pad4.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

struct packet_header {

    fbe_eobi::eobi_header eobi_header;
    fbe_eobi::appl_seq_num appl_seq_num;
    fbe_eobi::market_segment_id market_segment_id;
    fbe_eobi::partition_id partition_id;
    fbe_eobi::completion_indicator completion_indicator;
    fbe_eobi::appl_seq_reset_indicator appl_seq_reset_indicator;
    fbe_eobi::dscp dscp;
    fbe_eobi::pad4 pad4;
    fbe_eobi::transact_time transact_time;

    // parse method
    static packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<packet_header*>(buffer);
    }

    // parse method const
    static const packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(packet_header, eobi_header) == 0, "unexpected offset of packet_header::eobi_header");
static_assert(offsetof(packet_header, appl_seq_num) == 8, "unexpected offset of packet_header::appl_seq_num");
static_assert(offsetof(packet_header, market_segment_id) == 12, "unexpected offset of packet_header::market_segment_id");
static_assert(offsetof(packet_header, partition_id) == 16, "unexpected offset of packet_header::partition_id");
static_assert(offsetof(packet_header, completion_indicator) == 17, "unexpected offset of packet_header::completion_indicator");
static_assert(offsetof(packet_header, appl_seq_reset_indicator) == 18, "unexpected offset of packet_header::appl_seq_reset_indicator");
static_assert(offsetof(packet_header, dscp) == 19, "unexpected offset of packet_header::dscp");
static_assert(offsetof(packet_header, pad4) == 20, "unexpected offset of packet_header::pad4");
static_assert(offsetof(packet_header, transact_time) == 24, "unexpected offset of packet_header::transact_time");
static_assert(sizeof(packet_header) == 32, "unexpected sizeof packet_header");

#pragma pack(pop)
}
