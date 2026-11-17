// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/InsideMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/InsideId.hpp"
#include "../types/InsideAction.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidTimeMilli.hpp"
#include "../types/AskNumPricedMp.hpp"
#include "../types/BidNumPricedMp.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message is sent on the Quote Inside Channel and the Quote Inside with Global OTC data channel.
struct InsideMessage {

    ChannelSeqNum channel_seq_num;
    InsideId inside_id;
    InsideAction inside_action;
    QuoteFlags quote_flags;
    SecurityId security_id;
    AskPrice ask_price;
    AskSize ask_size;
    AskTimeMilli ask_time_milli;
    BidPrice bid_price;
    BidSize bid_size;
    BidTimeMilli bid_time_milli;
    AskNumPricedMp ask_num_priced_mp;
    BidNumPricedMp bid_num_priced_mp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 3;

    // parse method
    static InsideMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InsideMessage*>(buffer);
    }

    // parse method const
    static const InsideMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InsideMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InsideMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InsideMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
