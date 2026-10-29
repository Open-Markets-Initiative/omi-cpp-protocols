#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/Side.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// This message will be generated for unattributed orders accepted by the NASDAQ system.
struct AddOrderMessage {

    Nanoseconds nanoseconds;
    OrderReferenceNumber order_reference_number;
    Side side;
    Shares shares;
    Stock stock;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
