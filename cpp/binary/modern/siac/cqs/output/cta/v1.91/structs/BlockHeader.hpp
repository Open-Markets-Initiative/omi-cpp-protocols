#pragma once

#include "../types/Version.hpp"
#include "../types/BlockSize.hpp"
#include "../types/DataFeedIndicator.hpp"
#include "../types/RetransmissionIndicator.hpp"
#include "../types/BlockSequenceNumber.hpp"
#include "../types/MessagesInBlock.hpp"
#include "../structs/SipBlockTimestamp.hpp"
#include "../types/BlockChecksum.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct BlockHeader {

    Version version;
    BlockSize block_size;
    DataFeedIndicator data_feed_indicator;
    RetransmissionIndicator retransmission_indicator;
    BlockSequenceNumber block_sequence_number;
    MessagesInBlock messages_in_block;
    SipBlockTimestamp sip_block_timestamp;
    BlockChecksum block_checksum;

    // parse method
    static BlockHeader* parse(std::byte* buffer) {
        return reinterpret_cast<BlockHeader*>(buffer);
    }

    // parse method const
    static const BlockHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const BlockHeader*>(buffer);
    }
};

#pragma pack(pop)
}
