#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Size.hpp"
#include "../types/Instrument.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/OrderBookType.hpp"
#include "../types/Participant.hpp"
#include "../types/Depth.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Indicates the first order of a given side of an MBO snapshot.
struct AddOrderMboMessage {

    Timestamp timestamp;
    OrderId order_id;
    Side side;
    Size size;
    Instrument instrument;
    Price price;
    Reserved8 reserved_8;
    SourceVenue source_venue;
    OrderBookType order_book_type;
    Participant participant;
    Depth depth;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x41;

    // parse method
    static AddOrderMboMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMboMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMboMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMboMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMboMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMboMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
