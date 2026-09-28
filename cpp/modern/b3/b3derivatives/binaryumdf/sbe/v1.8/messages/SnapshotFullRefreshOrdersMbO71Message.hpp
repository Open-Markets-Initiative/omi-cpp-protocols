#pragma once

#include "../types/SecurityId.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

#pragma pack(push, 1)

// SnapshotFullRefresh_Orders_MBO_71Message
struct SnapshotFullRefreshOrdersMbO71Message {

    SecurityId security_id;

    // parse method
    static SnapshotFullRefreshOrdersMbO71Message* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshOrdersMbO71Message*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshOrdersMbO71Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshOrdersMbO71Message*>(buffer);
    }
};

#pragma pack(pop)
}
