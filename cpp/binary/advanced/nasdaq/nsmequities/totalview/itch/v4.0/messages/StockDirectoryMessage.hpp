#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/Stock.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/RoundLotsOnly.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Stock Directory Message
struct stock_directory_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::stock stock;
        itch_totalview::market_category market_category;
        itch_totalview::financial_status_indicator financial_status_indicator;
        itch_totalview::round_lot_size round_lot_size;
        itch_totalview::round_lots_only round_lots_only;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::stock_directory_message};

    fields_type fields;

    // parse method
    static stock_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<stock_directory_message*>(buffer);
    }

    // parse method const
    static const stock_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const stock_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(stock_directory_message::fields_type, nanoseconds) == 0, "unexpected offset of stock_directory_message::fields_type::nanoseconds");
static_assert(offsetof(stock_directory_message::fields_type, stock) == 4, "unexpected offset of stock_directory_message::fields_type::stock");
static_assert(offsetof(stock_directory_message::fields_type, market_category) == 10, "unexpected offset of stock_directory_message::fields_type::market_category");
static_assert(offsetof(stock_directory_message::fields_type, financial_status_indicator) == 11, "unexpected offset of stock_directory_message::fields_type::financial_status_indicator");
static_assert(offsetof(stock_directory_message::fields_type, round_lot_size) == 12, "unexpected offset of stock_directory_message::fields_type::round_lot_size");
static_assert(offsetof(stock_directory_message::fields_type, round_lots_only) == 16, "unexpected offset of stock_directory_message::fields_type::round_lots_only");
static_assert(sizeof(stock_directory_message::fields_type) == 17, "unexpected sizeof stock_directory_message::fields_type");
static_assert(sizeof(stock_directory_message) == sizeof(itch_totalview::message_header) + 17, "unexpected sizeof stock_directory_message");

#pragma pack(pop)
}
