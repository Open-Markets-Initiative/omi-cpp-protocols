#pragma once

#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/IssueCode.hpp"
#include "../types/UpdateNumber.hpp"
#include "../types/PacketNumber.hpp"
#include "../types/TotalNumberOfPackets.hpp"
#include "../types/UtilityFlag.hpp"
#include "../types/MessageCount.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

struct PacketHeader {

    MulticastGroupNumber multicast_group_number;
    NumberOfSystemReboots number_of_system_reboots;
    SequenceNumber sequence_number;
    IssueCode issue_code;
    UpdateNumber update_number;
    PacketNumber packet_number;
    TotalNumberOfPackets total_number_of_packets;
    UtilityFlag utility_flag;
    MessageCount message_count;

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
