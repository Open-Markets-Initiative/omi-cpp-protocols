#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// The Transaction Begin message indicates any subsequent messages, up to the accompanying Transaction End message, are all part of the same transaction block.
struct TransactionBegin {

    TimeOffset time_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xBC;

    // parse method
    static TransactionBegin* parse(std::byte* buffer) {
        return reinterpret_cast<TransactionBegin*>(buffer);
    }

    // parse method const
    static const TransactionBegin* parse(const std::byte* buffer) {
        return reinterpret_cast<const TransactionBegin*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TransactionBegin* parse(const MessageHeader* header) {
        return reinterpret_cast<const TransactionBegin*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
