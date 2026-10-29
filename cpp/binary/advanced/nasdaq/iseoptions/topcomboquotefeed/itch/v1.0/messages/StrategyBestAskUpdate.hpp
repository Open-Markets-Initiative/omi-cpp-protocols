#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/CustSize.hpp"
#include "../types/ProCustSize.hpp"
#include "../types/NttSize.hpp"
#include "../types/MarketSize.hpp"
#include "../types/NttMarketSize.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

// Strategy Best Ask Update
struct strategy_best_ask_update {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::strategy_id strategy_id;
        itch_topcomboquotefeed::quote_condition quote_condition;
        itch_topcomboquotefeed::price price;
        itch_topcomboquotefeed::size_type size;
        itch_topcomboquotefeed::cust_size cust_size;
        itch_topcomboquotefeed::pro_cust_size pro_cust_size;
        itch_topcomboquotefeed::ntt_size ntt_size;
        itch_topcomboquotefeed::market_size market_size;
        itch_topcomboquotefeed::ntt_market_size ntt_market_size;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::strategy_best_ask_update};

    fields_type fields;

    // parse method
    static strategy_best_ask_update* parse(std::byte* buffer) {
        return reinterpret_cast<strategy_best_ask_update*>(buffer);
    }

    // parse method const
    static const strategy_best_ask_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const strategy_best_ask_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(strategy_best_ask_update::fields_type, timestamp) == 0, "unexpected offset of strategy_best_ask_update::fields_type::timestamp");
static_assert(offsetof(strategy_best_ask_update::fields_type, strategy_id) == 6, "unexpected offset of strategy_best_ask_update::fields_type::strategy_id");
static_assert(offsetof(strategy_best_ask_update::fields_type, quote_condition) == 10, "unexpected offset of strategy_best_ask_update::fields_type::quote_condition");
static_assert(offsetof(strategy_best_ask_update::fields_type, price) == 11, "unexpected offset of strategy_best_ask_update::fields_type::price");
static_assert(offsetof(strategy_best_ask_update::fields_type, size) == 15, "unexpected offset of strategy_best_ask_update::fields_type::size");
static_assert(offsetof(strategy_best_ask_update::fields_type, cust_size) == 19, "unexpected offset of strategy_best_ask_update::fields_type::cust_size");
static_assert(offsetof(strategy_best_ask_update::fields_type, pro_cust_size) == 23, "unexpected offset of strategy_best_ask_update::fields_type::pro_cust_size");
static_assert(offsetof(strategy_best_ask_update::fields_type, ntt_size) == 27, "unexpected offset of strategy_best_ask_update::fields_type::ntt_size");
static_assert(offsetof(strategy_best_ask_update::fields_type, market_size) == 31, "unexpected offset of strategy_best_ask_update::fields_type::market_size");
static_assert(offsetof(strategy_best_ask_update::fields_type, ntt_market_size) == 35, "unexpected offset of strategy_best_ask_update::fields_type::ntt_market_size");
static_assert(sizeof(strategy_best_ask_update::fields_type) == 39, "unexpected sizeof strategy_best_ask_update::fields_type");
static_assert(sizeof(strategy_best_ask_update) == sizeof(itch_topcomboquotefeed::message_header) + 39, "unexpected sizeof strategy_best_ask_update");

#pragma pack(pop)
}
