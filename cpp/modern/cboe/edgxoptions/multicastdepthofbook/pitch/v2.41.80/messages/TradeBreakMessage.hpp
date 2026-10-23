#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ExecutionId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The Trade Break message is sent whenever an execution on Cboe is broken. Trade breaks are rare and only affect applications that rely upon Cboe execution-based data. Applications that simply build a Cboe book can ignore Trade Break messages.
struct TradeBreakMessage {

    TimeOffset time_offset;
    ExecutionId execution_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2C;

    // parse method
    static TradeBreakMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeBreakMessage*>(buffer);
    }

    // parse method const
    static const TradeBreakMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeBreakMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeBreakMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeBreakMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
