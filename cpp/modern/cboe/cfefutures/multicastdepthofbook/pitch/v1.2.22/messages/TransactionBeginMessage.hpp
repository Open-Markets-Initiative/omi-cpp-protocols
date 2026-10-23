#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block.
struct TransactionBeginMessage {

    TimeOffset time_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBC;

    // parse method
    static TransactionBeginMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TransactionBeginMessage*>(buffer);
    }

    // parse method const
    static const TransactionBeginMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TransactionBeginMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TransactionBeginMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TransactionBeginMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
