// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/MarketOpenMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/MarketOpen.hpp"
#include "../types/MarketClose.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message is sent out at 6 AM on all channels. The message can also be sent mid-day if a technical outage caused a temporary closure of the market.
struct MarketOpenMessage {

    ChannelSeqNum channel_seq_num;
    MarketOpen market_open;
    MarketClose market_close;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 13;

    // parse method
    static MarketOpenMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketOpenMessage*>(buffer);
    }

    // parse method const
    static const MarketOpenMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketOpenMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketOpenMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketOpenMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
