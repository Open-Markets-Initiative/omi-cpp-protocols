// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ReferencePriceMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/ReferencePriceId.hpp"
#include "../types/ReferencePriceAction.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidTimeMilli.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message is sent on the Reference Prices Channel. Size will always be set to 1.
struct ReferencePriceMessage {

    ChannelSeqNum channel_seq_num;
    ReferencePriceId reference_price_id;
    ReferencePriceAction reference_price_action;
    QuoteFlags quote_flags;
    SecurityId security_id;
    AskPrice ask_price;
    AskSize ask_size;
    AskTimeMilli ask_time_milli;
    BidPrice bid_price;
    BidSize bid_size;
    BidTimeMilli bid_time_milli;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 7;

    // parse method
    static ReferencePriceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReferencePriceMessage*>(buffer);
    }

    // parse method const
    static const ReferencePriceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReferencePriceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReferencePriceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ReferencePriceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
