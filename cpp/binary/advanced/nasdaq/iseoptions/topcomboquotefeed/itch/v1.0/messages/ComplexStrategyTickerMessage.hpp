#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/SizeType.hpp"
#include "../types/Volume.hpp"
#include "../types/High.hpp"
#include "../types/Low.hpp"
#include "../types/First.hpp"
#include "../types/TradeCondition.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

// Complex Strategy Ticker Message
struct complex_strategy_ticker_message {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::strategy_id strategy_id;
        itch_topcomboquotefeed::last_price last_price;
        itch_topcomboquotefeed::size_type size;
        itch_topcomboquotefeed::volume volume;
        itch_topcomboquotefeed::high high;
        itch_topcomboquotefeed::low low;
        itch_topcomboquotefeed::first first;
        itch_topcomboquotefeed::trade_condition trade_condition;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::complex_strategy_ticker_message};

    fields_type fields;

    // parse method
    static complex_strategy_ticker_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_strategy_ticker_message*>(buffer);
    }

    // parse method const
    static const complex_strategy_ticker_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_strategy_ticker_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_strategy_ticker_message::fields_type, timestamp) == 0, "unexpected offset of complex_strategy_ticker_message::fields_type::timestamp");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, strategy_id) == 6, "unexpected offset of complex_strategy_ticker_message::fields_type::strategy_id");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, last_price) == 10, "unexpected offset of complex_strategy_ticker_message::fields_type::last_price");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, size) == 18, "unexpected offset of complex_strategy_ticker_message::fields_type::size");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, volume) == 22, "unexpected offset of complex_strategy_ticker_message::fields_type::volume");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, high) == 26, "unexpected offset of complex_strategy_ticker_message::fields_type::high");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, low) == 34, "unexpected offset of complex_strategy_ticker_message::fields_type::low");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, first) == 42, "unexpected offset of complex_strategy_ticker_message::fields_type::first");
static_assert(offsetof(complex_strategy_ticker_message::fields_type, trade_condition) == 50, "unexpected offset of complex_strategy_ticker_message::fields_type::trade_condition");
static_assert(sizeof(complex_strategy_ticker_message::fields_type) == 51, "unexpected sizeof complex_strategy_ticker_message::fields_type");
static_assert(sizeof(complex_strategy_ticker_message) == sizeof(itch_topcomboquotefeed::message_header) + 51, "unexpected sizeof complex_strategy_ticker_message");

#pragma pack(pop)
}
