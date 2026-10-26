#pragma once

#include "../types/SnapshotLength.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

#pragma pack(push, 1)

// First message of a Snapshot Response sent from the Tops Snap server when a Snapshot Request is successful
struct SnapshotStartMessage {

    SnapshotLength snapshot_length;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 's';

    // parse method
    static SnapshotStartMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotStartMessage*>(buffer);
    }

    // parse method const
    static const SnapshotStartMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotStartMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotStartMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotStartMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
