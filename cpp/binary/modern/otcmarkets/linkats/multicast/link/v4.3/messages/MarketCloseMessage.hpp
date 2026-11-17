// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/MarketCloseMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/MarketCloseTimeMilli.hpp"
#include "../types/MarketMsgCt.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message is sent out at 5 PM on all channels. The message can also be sent mid-day if a technical outage causes a temporary closure of the market.
struct MarketCloseMessage {

    ChannelSeqNum channel_seq_num;
    MarketCloseTimeMilli market_close_time_milli;
    MarketMsgCt market_msg_ct;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 14;

    // parse method
    static MarketCloseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketCloseMessage*>(buffer);
    }

    // parse method const
    static const MarketCloseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketCloseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketCloseMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketCloseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
