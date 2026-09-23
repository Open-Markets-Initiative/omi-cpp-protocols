#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Shares.hpp"
#include "../types/Stock.hpp"
#include "../types/Price.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// This message will be generated for unattributed orders accepted by the Nasdaq system
struct AddOrderNoMpidAttributionMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    OrderReferenceNumber order_reference_number;
    BuySellIndicator buy_sell_indicator;
    Shares shares;
    Stock stock;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static AddOrderNoMpidAttributionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderNoMpidAttributionMessage*>(buffer);
    }

    // parse method const
    static const AddOrderNoMpidAttributionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderNoMpidAttributionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderNoMpidAttributionMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const AddOrderNoMpidAttributionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
