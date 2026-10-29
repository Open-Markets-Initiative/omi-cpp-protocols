#pragma once

#include "../structs/EobiHeader.hpp"
#include "../types/ApplSeqNum.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/PartitionId.hpp"
#include "../types/CompletionIndicator.hpp"
#include "../types/ApplSeqResetIndicator.hpp"
#include "../types/Pad5.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

struct PacketHeader {

    EobiHeader eobi_header;
    ApplSeqNum appl_seq_num;
    MarketSegmentId market_segment_id;
    PartitionId partition_id;
    CompletionIndicator completion_indicator;
    ApplSeqResetIndicator appl_seq_reset_indicator;
    Pad5 pad5;
    TransactTime transact_time;

    // parse method
    static PacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<PacketHeader*>(buffer);
    }

    // parse method const
    static const PacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const PacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
