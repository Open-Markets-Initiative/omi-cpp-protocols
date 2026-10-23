#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order added to the book with Mpid attribution
struct AddOrderMpidAttributionMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderReferenceNumber order_reference_number;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderBook order_book;
    Price price;
    Attribution attribution;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'F';

    // parse method
    static AddOrderMpidAttributionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMpidAttributionMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMpidAttributionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMpidAttributionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMpidAttributionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMpidAttributionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
