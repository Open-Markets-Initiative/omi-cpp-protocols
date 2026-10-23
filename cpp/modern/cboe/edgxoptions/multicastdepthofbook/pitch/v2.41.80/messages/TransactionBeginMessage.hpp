#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// Options Only. The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block. All PITCH messages corresponding to such an event would be included between a Transaction Begin message and Transaction End message. It is important to note that transaction blocks are currently used in US Options for symbol state transitions only, but may be expanded to other use cases with notice. Transaction Begin messages do not alter the book and can be ignored if messages are being used solely to build a book.
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
