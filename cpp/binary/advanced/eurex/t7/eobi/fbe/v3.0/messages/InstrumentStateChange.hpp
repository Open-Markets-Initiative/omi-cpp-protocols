#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad5.hpp"
#include "../types/TransactTime.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Instrument State Change
struct instrument_state_change {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::security_status security_status;
        fbe_eobi::security_trading_status security_trading_status;
        fbe_eobi::fast_market_indicator fast_market_indicator;
        fbe_eobi::pad5 pad5;
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
static_assert(offsetof(instrument_state_change::fields_type, fast_market_indicator) == 10, "unexpected offset of instrument_state_change::fields_type::fast_market_indicator");
static_assert(offsetof(instrument_state_change::fields_type, pad5) == 11, "unexpected offset of instrument_state_change::fields_type::pad5");
static_assert(offsetof(instrument_state_change::fields_type, transact_time) == 16, "unexpected offset of instrument_state_change::fields_type::transact_time");
static_assert(sizeof(instrument_state_change::fields_type) == 24, "unexpected sizeof instrument_state_change::fields_type");
static_assert(sizeof(instrument_state_change) == sizeof(fbe_eobi::message_header_comp) + 24, "unexpected sizeof instrument_state_change");

#pragma pack(pop)
}
