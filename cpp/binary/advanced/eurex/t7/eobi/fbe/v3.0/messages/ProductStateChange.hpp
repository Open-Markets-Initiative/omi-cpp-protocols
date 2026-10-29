#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad4.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Product State Change
struct product_state_change {

    struct fields_type {
        fbe_eobi::trading_session_id trading_session_id;
        fbe_eobi::trading_session_sub_id trading_session_sub_id;
        fbe_eobi::trad_ses_status trad_ses_status;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::pad4 pad4;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::product_state_change, {}};

    fields_type fields;

    // parse method
    static product_state_change* parse(std::byte* buffer) {
        return reinterpret_cast<product_state_change*>(buffer);
    }

    // parse method const
    static const product_state_change* parse(const std::byte* buffer) {
        return reinterpret_cast<const product_state_change*>(buffer);
    }

};

// layout verification
static_assert(offsetof(product_state_change::fields_type, trading_session_id) == 0, "unexpected offset of product_state_change::fields_type::trading_session_id");
static_assert(offsetof(product_state_change::fields_type, trading_session_sub_id) == 1, "unexpected offset of product_state_change::fields_type::trading_session_sub_id");
static_assert(offsetof(product_state_change::fields_type, trad_ses_status) == 2, "unexpected offset of product_state_change::fields_type::trad_ses_status");
static_assert(offsetof(product_state_change::fields_type, fast_market_indicator) == 3, "unexpected offset of product_state_change::fields_type::fast_market_indicator");
static_assert(offsetof(product_state_change::fields_type, pad4) == 4, "unexpected offset of product_state_change::fields_type::pad4");
static_assert(offsetof(product_state_change::fields_type, transact_time) == 8, "unexpected offset of product_state_change::fields_type::transact_time");
static_assert(sizeof(product_state_change::fields_type) == 16, "unexpected sizeof product_state_change::fields_type");
static_assert(sizeof(product_state_change) == sizeof(fbe_eobi::message_header_comp) + 16, "unexpected sizeof product_state_change");

#pragma pack(pop)
}
