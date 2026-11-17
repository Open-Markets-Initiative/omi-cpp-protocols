// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/TradeMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeAction.hpp"
#include "../types/TradeFlags.hpp"
#include "../types/SecurityId.hpp"
#include "../bitfields/TradeStatus.hpp"
#include "../types/Deprecated.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeTimeMilli.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// A Trade Message is created for every trade that occurs on OTC Markets OTC Link ATS.
struct TradeMessage {

    ChannelSeqNum channel_seq_num;
    TradeId trade_id;
    TradeAction trade_action;
    TradeFlags trade_flags;
    SecurityId security_id;
    TradeStatus trade_status;
    Deprecated deprecated;
    TradePrice trade_price;
    TradeSize trade_size;
    TradeTimeMilli trade_time_milli;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 17;

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
