#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/MarketStatus.hpp"
#include "../types/StatusFlag.hpp"
#include "../types/ShortSellingStatus.hpp"
#include "../types/PricingMethod.hpp"
#include "../types/BookCenterPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about the status of trading on a per-issue basis. Delivered when there is a change in the tag.
struct TradingStatusMessage {

    TimeMicroseconds time_microseconds;
    MarketStatus market_status;
    StatusFlag status_flag;
    ShortSellingStatus short_selling_status;
    PricingMethod pricing_method;
    BookCenterPrice book_center_price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static TradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingStatusMessage*>(buffer);
    }

    // parse method const
    static const TradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
