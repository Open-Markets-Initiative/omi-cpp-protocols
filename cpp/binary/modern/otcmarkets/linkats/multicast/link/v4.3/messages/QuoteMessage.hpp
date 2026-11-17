// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/QuoteMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/QuoteId.hpp"
#include "../types/QuoteAction.hpp"
#include "../bitfields/QuoteFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Mpid.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskQap.hpp"
#include "../types/AskTimeMilli.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidQap.hpp"
#include "../types/BidTimeMilli.hpp"
#include "../types/QuoteReferenceId.hpp"
#include "../bitfields/ExtendedQuoteFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message is sent on the Quote Book channel and the Quote Book with Global OTC data channel.
struct QuoteMessage {

    ChannelSeqNum channel_seq_num;
    QuoteId quote_id;
    QuoteAction quote_action;
    QuoteFlags quote_flags;
    SecurityId security_id;
    Mpid mpid;
    AskPrice ask_price;
    AskSize ask_size;
    AskQap ask_qap;
    AskTimeMilli ask_time_milli;
    BidPrice bid_price;
    BidSize bid_size;
    BidQap bid_qap;
    BidTimeMilli bid_time_milli;
    QuoteReferenceId quote_reference_id;
    ExtendedQuoteFlags extended_quote_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 1;

    // parse method
    static QuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<QuoteMessage*>(buffer);
    }

    // parse method const
    static const QuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const QuoteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const QuoteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const QuoteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
