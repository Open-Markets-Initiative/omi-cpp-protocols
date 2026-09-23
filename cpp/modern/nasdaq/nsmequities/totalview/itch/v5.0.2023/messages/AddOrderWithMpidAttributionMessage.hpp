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
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message will be generated for attributed orders and quotations accepted by the Nasdaq system
struct AddOrderWithMpidAttributionMessage {

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
    static AddOrderWithMpidAttributionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderWithMpidAttributionMessage*>(buffer);
    }

    // parse method const
    static const AddOrderWithMpidAttributionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderWithMpidAttributionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderWithMpidAttributionMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const AddOrderWithMpidAttributionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
