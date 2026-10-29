#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// This message will be generated for attributed orders and quotations accepted by the NASDAQ system.
struct AddOrderWithMpidMessage {

    Nanoseconds nanoseconds;
    OrderReferenceNumber order_reference_number;
    Side side;
    Shares shares;
    Stock stock;
    Price price;
    Attribution attribution;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'F';

    // parse method
    static AddOrderWithMpidMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderWithMpidMessage*>(buffer);
    }

    // parse method const
    static const AddOrderWithMpidMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderWithMpidMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderWithMpidMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderWithMpidMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
