// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/SecurityMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/Symbol.hpp"
#include "../types/LastUpdateMilli.hpp"
#include "../types/SecurityAction.hpp"
#include "../types/AssetClass.hpp"
#include "../types/SecurityId.hpp"
#include "../bitfields/SecurityFlags.hpp"
#include "../types/Tier.hpp"
#include "../types/ReportingStatus.hpp"
#include "../types/SecurityStatus.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// The Security Message is included in all the quote channels and provides basic security attribute information.
struct SecurityMessage {

    ChannelSeqNum channel_seq_num;
    Symbol symbol;
    LastUpdateMilli last_update_milli;
    SecurityAction security_action;
    AssetClass asset_class;
    SecurityId security_id;
    SecurityFlags security_flags;
    Tier tier;
    ReportingStatus reporting_status;
    SecurityStatus security_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 9;

    // parse method
    static SecurityMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityMessage*>(buffer);
    }

    // parse method const
    static const SecurityMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
