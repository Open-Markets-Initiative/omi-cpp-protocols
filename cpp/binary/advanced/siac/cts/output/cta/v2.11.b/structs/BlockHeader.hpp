#pragma once

#include <cstddef>
#include "../types/Version.hpp"
#include "../types/BlockSize.hpp"
#include "../types/DataFeedIndicator.hpp"
#include "../types/RetransmissionIndicator.hpp"
#include "../types/BlockSequenceNumber.hpp"
#include "../types/MessagesInBlock.hpp"
#include "../structs/SipBlockTimestamp.hpp"
#include "../types/BlockChecksum.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

struct block_header {

    cta_output::version version;
    cta_output::block_size block_size;
    cta_output::data_feed_indicator data_feed_indicator;
    cta_output::retransmission_indicator retransmission_indicator;
    cta_output::block_sequence_number block_sequence_number;
    cta_output::messages_in_block messages_in_block;
    cta_output::sip_block_timestamp sip_block_timestamp;
    cta_output::block_checksum block_checksum;

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
static_assert(offsetof(block_header, block_sequence_number) == 5, "unexpected offset of block_header::block_sequence_number");
static_assert(offsetof(block_header, messages_in_block) == 9, "unexpected offset of block_header::messages_in_block");
static_assert(offsetof(block_header, sip_block_timestamp) == 10, "unexpected offset of block_header::sip_block_timestamp");
static_assert(offsetof(block_header, block_checksum) == 18, "unexpected offset of block_header::block_checksum");
static_assert(sizeof(block_header) == 20, "unexpected sizeof block_header");

#pragma pack(pop)
}
