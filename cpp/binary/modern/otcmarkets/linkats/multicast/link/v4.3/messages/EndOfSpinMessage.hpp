// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/EndOfSpinMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/SpinType.hpp"
#include "../types/SpinMsgCt.hpp"
#include "../types/SpinEndTimeMilli.hpp"
#include "../types/SpinLastSeqNum.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message appears on all quote channels and indicates the end of a spin message cycle.
struct EndOfSpinMessage {

    ChannelSeqNum channel_seq_num;
    SpinType spin_type;
    SpinMsgCt spin_msg_ct;
    SpinEndTimeMilli spin_end_time_milli;
    SpinLastSeqNum spin_last_seq_num;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 12;

    // parse method
    static EndOfSpinMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfSpinMessage*>(buffer);
    }

    // parse method const
    static const EndOfSpinMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfSpinMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfSpinMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfSpinMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
