#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/Pad3.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Instrument State Change
struct instrument_state_change {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::security_status security_status;
        fbe_eobi::security_trading_status security_trading_status;
        fbe_eobi::market_condition market_condition;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::security_trading_event security_trading_event;
        fbe_eobi::pad3 pad3;
        fbe_eobi::transact_time transact_time;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::instrument_state_change, {}};

    fields_type fields;

    // parse method
    static instrument_state_change* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_state_change*>(buffer);
    }

    // parse method const
    static const instrument_state_change* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_state_change*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_state_change::fields_type, security_id) == 0, "unexpected offset of instrument_state_change::fields_type::security_id");
static_assert(offsetof(instrument_state_change::fields_type, security_status) == 8, "unexpected offset of instrument_state_change::fields_type::security_status");
static_assert(offsetof(instrument_state_change::fields_type, security_trading_status) == 9, "unexpected offset of instrument_state_change::fields_type::security_trading_status");
static_assert(offsetof(instrument_state_change::fields_type, market_condition) == 10, "unexpected offset of instrument_state_change::fields_type::market_condition");
static_assert(offsetof(instrument_state_change::fields_type, fast_market_indicator) == 11, "unexpected offset of instrument_state_change::fields_type::fast_market_indicator");
static_assert(offsetof(instrument_state_change::fields_type, security_trading_event) == 12, "unexpected offset of instrument_state_change::fields_type::security_trading_event");
static_assert(offsetof(instrument_state_change::fields_type, pad3) == 13, "unexpected offset of instrument_state_change::fields_type::pad3");
static_assert(offsetof(instrument_state_change::fields_type, transact_time) == 16, "unexpected offset of instrument_state_change::fields_type::transact_time");
static_assert(sizeof(instrument_state_change::fields_type) == 24, "unexpected sizeof instrument_state_change::fields_type");
static_assert(sizeof(instrument_state_change) == sizeof(fbe_eobi::message_header_comp) + 24, "unexpected sizeof instrument_state_change");

#pragma pack(pop)
}
