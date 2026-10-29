#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad4.hpp"
#include "../types/TransactTime.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Product State Change Message
struct product_state_change_message {

    struct fields_type {
        fbe_eobi::trading_session_id trading_session_id;
        fbe_eobi::trading_session_sub_id trading_session_sub_id;
        fbe_eobi::trad_ses_status trad_ses_status;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::pad_4 pad_4;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::product_state_change_message, {}};

    fields_type fields;

    // parse method
    static product_state_change_message* parse(std::byte* buffer) {
        return reinterpret_cast<product_state_change_message*>(buffer);
    }

    // parse method const
    static const product_state_change_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const product_state_change_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(product_state_change_message::fields_type, trading_session_id) == 0, "unexpected offset of product_state_change_message::fields_type::trading_session_id");
static_assert(offsetof(product_state_change_message::fields_type, trading_session_sub_id) == 1, "unexpected offset of product_state_change_message::fields_type::trading_session_sub_id");
static_assert(offsetof(product_state_change_message::fields_type, trad_ses_status) == 2, "unexpected offset of product_state_change_message::fields_type::trad_ses_status");
static_assert(offsetof(product_state_change_message::fields_type, fast_market_indicator) == 3, "unexpected offset of product_state_change_message::fields_type::fast_market_indicator");
static_assert(offsetof(product_state_change_message::fields_type, pad_4) == 4, "unexpected offset of product_state_change_message::fields_type::pad_4");
static_assert(offsetof(product_state_change_message::fields_type, transact_time) == 8, "unexpected offset of product_state_change_message::fields_type::transact_time");
static_assert(sizeof(product_state_change_message::fields_type) == 16, "unexpected sizeof product_state_change_message::fields_type");
static_assert(sizeof(product_state_change_message) == sizeof(fbe_eobi::message_header) + 16, "unexpected sizeof product_state_change_message");

#pragma pack(pop)
}
