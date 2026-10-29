#pragma once

#include "../types/PktSize.hpp"
#include "../types/DeliveryFlag.hpp"
#include "../types/NumberMsgs.hpp"
#include "../types/SeqNum.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

#pragma pack(push, 1)

struct PacketHeader {

    PktSize pkt_size;
    DeliveryFlag delivery_flag;
    NumberMsgs number_msgs;
    SeqNum seq_num;
    SendTime send_time;

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
