#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// The message is sent when an order or a side of a quote is being cancelled. All remaining contracts are no longer accessible so the side should be removed from the book.
struct SingleSideDeleteMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    ReferenceNumber reference_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static SingleSideDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SingleSideDeleteMessage*>(buffer);
    }

    // parse method const
    static const SingleSideDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SingleSideDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SingleSideDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SingleSideDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
