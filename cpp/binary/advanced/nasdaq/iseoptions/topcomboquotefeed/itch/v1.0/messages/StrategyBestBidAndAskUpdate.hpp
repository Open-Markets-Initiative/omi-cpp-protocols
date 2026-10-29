#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidCustSize.hpp"
#include "../types/BidProCustSize.hpp"
#include "../types/BidNttSize.hpp"
#include "../types/BidMarketSize.hpp"
#include "../types/BidNttMarketSize.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"
#include "../types/AskCustSize.hpp"
#include "../types/AskProCustSize.hpp"
#include "../types/AskNttSize.hpp"
#include "../types/AskMarketSize.hpp"
#include "../types/AskNttMarketSize.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

#pragma pack(push, 1)

// Strategy Best Bid And Ask Update
struct strategy_best_bid_and_ask_update {

    struct fields_type {
        itch_topcomboquotefeed::timestamp timestamp;
        itch_topcomboquotefeed::strategy_id strategy_id;
        itch_topcomboquotefeed::quote_condition quote_condition;
        itch_topcomboquotefeed::bid_price bid_price;
        itch_topcomboquotefeed::bid_size bid_size;
        itch_topcomboquotefeed::bid_cust_size bid_cust_size;
        itch_topcomboquotefeed::bid_pro_cust_size bid_pro_cust_size;
        itch_topcomboquotefeed::bid_ntt_size bid_ntt_size;
        itch_topcomboquotefeed::bid_market_size bid_market_size;
        itch_topcomboquotefeed::bid_ntt_market_size bid_ntt_market_size;
        itch_topcomboquotefeed::ask_price ask_price;
        itch_topcomboquotefeed::ask_size ask_size;
        itch_topcomboquotefeed::ask_cust_size ask_cust_size;
        itch_topcomboquotefeed::ask_pro_cust_size ask_pro_cust_size;
        itch_topcomboquotefeed::ask_ntt_size ask_ntt_size;
        itch_topcomboquotefeed::ask_market_size ask_market_size;
        itch_topcomboquotefeed::ask_ntt_market_size ask_ntt_market_size;
    };

    itch_topcomboquotefeed::message_header header = {std::uint16_t(sizeof(itch_topcomboquotefeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::strategy_best_bid_and_ask_update};

    fields_type fields;

    // parse method
    static strategy_best_bid_and_ask_update* parse(std::byte* buffer) {
        return reinterpret_cast<strategy_best_bid_and_ask_update*>(buffer);
    }

    // parse method const
    static const strategy_best_bid_and_ask_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const strategy_best_bid_and_ask_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, timestamp) == 0, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::timestamp");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, strategy_id) == 6, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::strategy_id");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, quote_condition) == 10, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::quote_condition");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_price) == 11, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_price");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_size) == 15, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_cust_size) == 19, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_cust_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_pro_cust_size) == 23, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_pro_cust_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_ntt_size) == 27, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_ntt_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_market_size) == 31, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_market_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, bid_ntt_market_size) == 35, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::bid_ntt_market_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_price) == 39, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_price");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_size) == 43, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_cust_size) == 47, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_cust_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_pro_cust_size) == 51, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_pro_cust_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_ntt_size) == 55, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_ntt_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_market_size) == 59, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_market_size");
static_assert(offsetof(strategy_best_bid_and_ask_update::fields_type, ask_ntt_market_size) == 63, "unexpected offset of strategy_best_bid_and_ask_update::fields_type::ask_ntt_market_size");
static_assert(sizeof(strategy_best_bid_and_ask_update::fields_type) == 67, "unexpected sizeof strategy_best_bid_and_ask_update::fields_type");
static_assert(sizeof(strategy_best_bid_and_ask_update) == sizeof(itch_topcomboquotefeed::message_header) + 67, "unexpected sizeof strategy_best_bid_and_ask_update");

#pragma pack(pop)
}
