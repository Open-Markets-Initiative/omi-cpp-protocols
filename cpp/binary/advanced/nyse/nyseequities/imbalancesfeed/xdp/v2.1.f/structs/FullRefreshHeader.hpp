#pragma once

#include <cstddef>
#include "../types/LastSeqNum.hpp"
#include "../types/LastSymbolSeqNum.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

namespace xdp_imbalancesfeed = ::nyse::nyseequities::imbalancesfeed::xdp::v2_1_f;

#pragma pack(push, 1)

struct full_refresh_header {

    xdp_imbalancesfeed::last_seq_num last_seq_num;
    xdp_imbalancesfeed::last_symbol_seq_num last_symbol_seq_num;

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
