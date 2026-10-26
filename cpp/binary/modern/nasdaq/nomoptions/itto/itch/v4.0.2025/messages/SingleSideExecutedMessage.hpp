#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/ReferenceNumber.hpp"
#include "../types/ExecutedContracts.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// This message is sent whenever a Side order is executed in whole or in part. It is possible to receive several Single Side Executed Messages for the same Side order if that Side order is executed in several parts. The multiple Single Side Executed Messages on the same order are cumulative. By combining the executions received separately via two types of Single Side Executed Messages and Trade Messages, it is possible to build a complete view of all non-auction executions that happen on NASDAQ. Auction execution information is available in one bulk print via the Auction Trade Message.
struct SingleSideExecutedMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    ReferenceNumber reference_number;
    ExecutedContracts executed_contracts;
    CrossNumber cross_number;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static SingleSideExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SingleSideExecutedMessage*>(buffer);
    }

    // parse method const
    static const SingleSideExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SingleSideExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SingleSideExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SingleSideExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
