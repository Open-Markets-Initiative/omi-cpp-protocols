#pragma once

#include "../structs/OrderDetailsComp.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct SnapshotOrder {

    OrderDetailsComp order_details_comp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13602;

    // parse method
    static SnapshotOrder* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotOrder*>(buffer);
    }

    // parse method const
    static const SnapshotOrder* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotOrder*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SnapshotOrder* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const SnapshotOrder*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
