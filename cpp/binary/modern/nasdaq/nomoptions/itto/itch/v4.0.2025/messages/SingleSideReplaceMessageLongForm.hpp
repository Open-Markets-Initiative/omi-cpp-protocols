#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalReferenceNumber.hpp"
#include "../types/NewReferenceNumber.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message is sent whenever an order or one side of a quote on the book is replaced. The replacement has a new sequence number and replaces the prior sequence number.
struct SingleSideReplaceMessageLongForm {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    OriginalReferenceNumber original_reference_number;
    NewReferenceNumber new_reference_number;
    PriceLong price_long;
    VolumeLong volume_long;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static SingleSideReplaceMessageLongForm* parse(std::byte* buffer) {
        return reinterpret_cast<SingleSideReplaceMessageLongForm*>(buffer);
    }

    // parse method const
    static const SingleSideReplaceMessageLongForm* parse(const std::byte* buffer) {
        return reinterpret_cast<const SingleSideReplaceMessageLongForm*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SingleSideReplaceMessageLongForm* parse(const MessageHeader* header) {
        return reinterpret_cast<const SingleSideReplaceMessageLongForm*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
