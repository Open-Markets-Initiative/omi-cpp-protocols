#pragma once

#include <cstddef>
#include "../types/LastSeqNum.hpp"
#include "../types/LastSymbolSeqNum.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

namespace pillar_bbo = ::nyse::nationalequities::bbo::pillar::v2_5_d;

#pragma pack(push, 1)

struct full_refresh_header {

    pillar_bbo::last_seq_num last_seq_num;
    pillar_bbo::last_symbol_seq_num last_symbol_seq_num;

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
