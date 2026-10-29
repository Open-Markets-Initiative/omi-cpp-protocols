#pragma once

#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/OpenState.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

#pragma pack(push, 1)

// The options system uses this administrative message to indicate when an strategy has completed the opening process and is now available for auto execution or when the option has closed and is no longer available for auto execution.
struct StrategyOpenClosedMessage {

    Timestamp timestamp;
    StrategyId strategy_id;
    OpenState open_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static StrategyOpenClosedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StrategyOpenClosedMessage*>(buffer);
    }

    // parse method const
    static const StrategyOpenClosedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StrategyOpenClosedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StrategyOpenClosedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StrategyOpenClosedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
