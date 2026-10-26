#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Stock.hpp"
#include "../types/InterestFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

#pragma pack(push, 1)

// Identifies a retail interest indication of the Bid, Ask or both the Bid and Ask for NASDAQ-listed securities.
struct RetailInterestMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    Stock stock;
    InterestFlag interest_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'N';

    // parse method
    static RetailInterestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetailInterestMessage*>(buffer);
    }

    // parse method const
    static const RetailInterestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetailInterestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetailInterestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RetailInterestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
