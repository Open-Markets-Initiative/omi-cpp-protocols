#pragma once

#include <cstddef>
#include "../types/LastSeqNum.hpp"
#include "../types/LastSymbolSeqNum.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

struct full_refresh_header {

    pillar_topfeed::last_seq_num last_seq_num;
    pillar_topfeed::last_symbol_seq_num last_symbol_seq_num;

    // parse method
    static full_refresh_header* parse(std::byte* buffer) {
        return reinterpret_cast<full_refresh_header*>(buffer);
    }

    // parse method const
    static const full_refresh_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const full_refresh_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(full_refresh_header, last_seq_num) == 0, "unexpected offset of full_refresh_header::last_seq_num");
static_assert(offsetof(full_refresh_header, last_symbol_seq_num) == 4, "unexpected offset of full_refresh_header::last_symbol_seq_num");
static_assert(sizeof(full_refresh_header) == 8, "unexpected sizeof full_refresh_header");

#pragma pack(pop)
}
