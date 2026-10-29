#pragma once

#include "../types/PacketSize.hpp"
#include "../types/DeliveryFlag.hpp"
#include "../types/MessageCount.hpp"
#include "../types/SequenceNumber.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

#pragma pack(push, 1)

struct PacketHeader {

    PacketSize packet_size;
    DeliveryFlag delivery_flag;
    MessageCount message_count;
    SequenceNumber sequence_number;
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
