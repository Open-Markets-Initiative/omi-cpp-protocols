// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/ReferencePriceUpdateMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/ReferencePriceId.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/TimeMilli.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// Quote update information for the Reference Price channel.
struct ReferencePriceUpdateMessage {

    ChannelSeqNum channel_seq_num;
    ReferencePriceId reference_price_id;
    QuoteFlags quote_flags;
    Price price;
    Size size;
    TimeMilli time_milli;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 8;

    // parse method
    static ReferencePriceUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReferencePriceUpdateMessage*>(buffer);
    }

    // parse method const
    static const ReferencePriceUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReferencePriceUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReferencePriceUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ReferencePriceUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
