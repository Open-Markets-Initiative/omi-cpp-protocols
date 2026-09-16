#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeMicroseconds.hpp"
#include "../types/MarketStatus.hpp"
#include "../types/StatusFlag.hpp"
#include "../types/ShortSellingStatus.hpp"
#include "../types/PricingMethod.hpp"
#include "../types/BookCenterPrice.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        flex_marketbyorder::time_microseconds time_microseconds;
        flex_marketbyorder::market_status market_status;
        flex_marketbyorder::status_flag status_flag;
        flex_marketbyorder::short_selling_status short_selling_status;
        flex_marketbyorder::pricing_method pricing_method;
        flex_marketbyorder::book_center_price book_center_price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::trading_status_message};

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, time_microseconds) == 0, "unexpected offset of trading_status_message::fields_type::time_microseconds");
static_assert(offsetof(trading_status_message::fields_type, market_status) == 4, "unexpected offset of trading_status_message::fields_type::market_status");
static_assert(offsetof(trading_status_message::fields_type, status_flag) == 5, "unexpected offset of trading_status_message::fields_type::status_flag");
static_assert(offsetof(trading_status_message::fields_type, short_selling_status) == 7, "unexpected offset of trading_status_message::fields_type::short_selling_status");
static_assert(offsetof(trading_status_message::fields_type, pricing_method) == 8, "unexpected offset of trading_status_message::fields_type::pricing_method");
static_assert(offsetof(trading_status_message::fields_type, book_center_price) == 9, "unexpected offset of trading_status_message::fields_type::book_center_price");
static_assert(sizeof(trading_status_message::fields_type) == 17, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(message_header) + 17, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
