#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossId.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Price4.hpp"
#include "../types/Volume.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The Trade Report message will be used to relay execution system transactions that are reported during the current business day. The options system only reports one-side of a trade execution on the feed and other data feed products.
struct TradeReportMessage {

    Nanoseconds nanoseconds;
    OptionId option_id;
    CrossId cross_id;
    TradeCondition trade_condition;
    Price4 price_4;
    Volume volume;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static TradeReportMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReportMessage*>(buffer);
    }

    // parse method const
    static const TradeReportMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReportMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReportMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeReportMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
