// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/StartOfSpinMessage.hpp
#pragma once

#include "../types/ChannelSeqNum.hpp"
#include "../types/SpinType.hpp"
#include "../types/SpinStartTimeMilli.hpp"
#include "../types/SpinLastSeqNum.hpp"
#include "../structs/MessageHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

// This message appears on all quote channels and indicates the beginning of a spin message cycle.
struct StartOfSpinMessage {

    ChannelSeqNum channel_seq_num;
    SpinType spin_type;
    SpinStartTimeMilli spin_start_time_milli;
    SpinLastSeqNum spin_last_seq_num;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 11;

    // parse method
    static StartOfSpinMessage* parse(std::byte* buffer) {
        return reinterpret_cast<StartOfSpinMessage*>(buffer);
    }

    // parse method const
    static const StartOfSpinMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const StartOfSpinMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const StartOfSpinMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const StartOfSpinMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
