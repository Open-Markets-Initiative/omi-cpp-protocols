#pragma once

#include <cstddef>
#include "../types/Version.hpp"
#include "../types/BlockSize.hpp"
#include "../types/DataFeedIndicator.hpp"
#include "../types/RetransmissionIndicator.hpp"
#include "../types/SessionIndicator.hpp"
#include "../types/BlockSequenceNumber.hpp"
#include "../types/MessagesInBlock.hpp"
#include "../structs/BlockTimestamp.hpp"
#include "../types/BlockChecksum.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct block_header {

    obi_output::version version;
    obi_output::block_size block_size;
    obi_output::data_feed_indicator data_feed_indicator;
    obi_output::retransmission_indicator retransmission_indicator;
    obi_output::session_indicator session_indicator;
    obi_output::block_sequence_number block_sequence_number;
    obi_output::messages_in_block messages_in_block;
    obi_output::block_timestamp block_timestamp;
    obi_output::block_checksum block_checksum;

    // parse method
    static block_header* parse(std::byte* buffer) {
        return reinterpret_cast<block_header*>(buffer);
    }

    // parse method const
    static const block_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const block_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(block_header, version) == 0, "unexpected offset of block_header::version");
static_assert(offsetof(block_header, block_size) == 1, "unexpected offset of block_header::block_size");
static_assert(offsetof(block_header, data_feed_indicator) == 3, "unexpected offset of block_header::data_feed_indicator");
static_assert(offsetof(block_header, retransmission_indicator) == 4, "unexpected offset of block_header::retransmission_indicator");
static_assert(offsetof(block_header, session_indicator) == 5, "unexpected offset of block_header::session_indicator");
static_assert(offsetof(block_header, block_sequence_number) == 6, "unexpected offset of block_header::block_sequence_number");
static_assert(offsetof(block_header, messages_in_block) == 10, "unexpected offset of block_header::messages_in_block");
static_assert(offsetof(block_header, block_timestamp) == 11, "unexpected offset of block_header::block_timestamp");
static_assert(offsetof(block_header, block_checksum) == 19, "unexpected offset of block_header::block_checksum");
static_assert(sizeof(block_header) == 21, "unexpected sizeof block_header");

#pragma pack(pop)
}
