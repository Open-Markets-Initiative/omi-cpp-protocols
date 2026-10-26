#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TransactionTime.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/ExecutedSize.hpp"
#include "../types/Instrument.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeType.hpp"
#include "../types/AuctionType.hpp"
#include "../bitfields/TradeFlags.hpp"
#include "../types/HiddenExecutionIndicator.hpp"
#include "../types/TradeQualifier.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Sent to indicate trades executed on supported markets.
struct TradeMessage {

    Timestamp timestamp;
    TransactionTime transaction_time;
    SourceVenue source_venue;
    ExecutedSize executed_size;
    Instrument instrument;
    Price price;
    Reserved8 reserved_8;
    TradeId trade_id;
    TradeType trade_type;
    AuctionType auction_type;
    TradeFlags trade_flags;
    HiddenExecutionIndicator hidden_execution_indicator;
    TradeQualifier trade_qualifier;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x50;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
