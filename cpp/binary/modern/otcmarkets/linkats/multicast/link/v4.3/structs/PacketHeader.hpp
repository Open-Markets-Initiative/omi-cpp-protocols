// OtcMarkets.LinkAts.Multicast.Link.v4.3: structs/PacketHeader.hpp
#pragma once

#include "../types/PacketSize.hpp"
#include "../types/SeqNum.hpp"
#include "../bitfields/PacketFlag.hpp"
#include "../types/MessageCount.hpp"
#include "../types/PacketMilli.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

#pragma pack(push, 1)

struct PacketHeader {

    PacketSize packet_size;
    SeqNum seq_num;
    PacketFlag packet_flag;
    MessageCount message_count;
    PacketMilli packet_milli;

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
