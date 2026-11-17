// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/PacketHeader.hpp
#pragma once

#include "../types/Version.hpp"
#include "../types/PacketLength.hpp"
#include "../types/SendingTime.hpp"
#include "../types/MessageCount.hpp"
#include "../types/FirstMsgSeqNum.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct PacketHeader {

    Version version;
    PacketLength packet_length;
    SendingTime sending_time;
    MessageCount message_count;
    FirstMsgSeqNum first_msg_seq_num;

    // parse method
    static PacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<PacketHeader*>(buffer);
    }

    // parse method const
    static const PacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const PacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
