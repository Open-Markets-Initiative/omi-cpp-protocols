#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"
#include "../types/ChangeReason.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message is sent whenever an order or a side of a quote is being updated for price and (or) contracts. The reference number associated with the order quote is unchanged.
struct SingleSideChangeMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    ReferenceNumber reference_number;
    ChangeReason change_reason;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'G';

    // parse method
    static SingleSideChangeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SingleSideChangeMessage*>(buffer);
    }

    // parse method const
    static const SingleSideChangeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SingleSideChangeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SingleSideChangeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SingleSideChangeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
