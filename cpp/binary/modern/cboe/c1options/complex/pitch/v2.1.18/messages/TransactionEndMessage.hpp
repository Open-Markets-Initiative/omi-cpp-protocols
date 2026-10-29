#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// The Transaction End message indicates that a transaction indicated by a previous Transaction Begin message has completed.
struct TransactionEndMessage {

    TimeOffset time_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBD;

    // parse method
    static TransactionEndMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TransactionEndMessage*>(buffer);
    }

    // parse method const
    static const TransactionEndMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TransactionEndMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TransactionEndMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TransactionEndMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
