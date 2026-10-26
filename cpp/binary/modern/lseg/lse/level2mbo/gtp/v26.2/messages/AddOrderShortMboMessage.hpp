#pragma once

#include "../types/OrderId.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/Participant.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Used to indicate individual orders of an MBO snapshot.
struct AddOrderShortMboMessage {

    OrderId order_id;
    Size size;
    Price price;
    Reserved8 reserved_8;
    Participant participant;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x65;

    // parse method
    static AddOrderShortMboMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderShortMboMessage*>(buffer);
    }

    // parse method const
    static const AddOrderShortMboMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderShortMboMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderShortMboMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderShortMboMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
