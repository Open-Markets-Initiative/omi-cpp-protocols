#pragma once

#include "../types/LastSeqNum.hpp"
#include "../types/LastSymbolSeqNum.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

struct FullRefreshHeader {

    LastSeqNum last_seq_num;
    LastSymbolSeqNum last_symbol_seq_num;

    // parse method
    static FullRefreshHeader* parse(std::byte* buffer) {
        return reinterpret_cast<FullRefreshHeader*>(buffer);
    }

    // parse method const
    static const FullRefreshHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const FullRefreshHeader*>(buffer);
    }
};

#pragma pack(pop)
}
