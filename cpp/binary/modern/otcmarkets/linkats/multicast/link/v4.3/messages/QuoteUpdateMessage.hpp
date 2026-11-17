// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/QuoteUpdateMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/QuoteId.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/Qap.hpp"
#include "../types/QuoteTimeMilli.hpp"
#include "../types/QuoteReferenceId.hpp"
#include "../bitfields/ExtendedQuoteFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// Quote update information for the Quote Book channel and the Quote Book with Global OTC data channel.
struct QuoteUpdateMessage {

    ChannelSeqNum channel_seq_num;
    QuoteId quote_id;
    QuoteFlags quote_flags;
    Price price;
    Size size;
    Qap qap;
    QuoteTimeMilli quote_time_milli;
    QuoteReferenceId quote_reference_id;
    ExtendedQuoteFlags extended_quote_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 2;

    // parse method
    static QuoteUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteUpdateMessage*>(buffer);
    }

    // parse method const
    static const QuoteUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
