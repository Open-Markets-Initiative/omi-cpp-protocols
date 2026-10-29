#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

#pragma pack(push, 1)

// This message will be generated for attributed orders and quotations accepted by the Nasdaq Texas system.
struct AddOrderMpidAttributionMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    BuySellIndicator buy_sell_indicator;
    Shares shares;
    Stock stock;
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
