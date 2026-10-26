#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order added to the book without Mpid attribution
struct AddOrderMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderReferenceNumber order_reference_number;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderBook order_book;
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
