// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/InsideUpdateMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/InsideId.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/InsideTimeMilli.hpp"
#include "../types/NumPricedMp.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// Quote update information for the Quote Inside channel and the Quote Inside with Global OTC data channel.
struct InsideUpdateMessage {

    ChannelSeqNum channel_seq_num;
    InsideId inside_id;
    QuoteFlags quote_flags;
    Price price;
    Size size;
    InsideTimeMilli inside_time_milli;
    NumPricedMp num_priced_mp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 4;

    // parse method
    static InsideUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InsideUpdateMessage*>(buffer);
    }

    // parse method const
    static const InsideUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InsideUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InsideUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const InsideUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
