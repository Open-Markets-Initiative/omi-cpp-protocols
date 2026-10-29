#pragma once

#include "../structs/OrderDetails.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Represents each individual order or quote in a snapshot cycle on the snapshot channel.
struct SnapshotOrderMessage {

    OrderDetails order_details;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13602;

    // parse method
    static SnapshotOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotOrderMessage*>(buffer);
    }

    // parse method const
    static const SnapshotOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SnapshotOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
