#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/TsRecv.hpp"
#include "../types/StatusAction.hpp"
#include "../types/StatusReason.hpp"
#include "../types/TradingEvent.hpp"
#include "../types/IsTrading.hpp"
#include "../types/IsQuoting.hpp"
#include "../types/IsShortSellRestricted.hpp"
#include "../types/Reserved7.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Status Msg
struct status_msg {

    struct fields_type {
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::status_action status_action;
        dbn_normalized::status_reason status_reason;
        dbn_normalized::trading_event trading_event;
        dbn_normalized::is_trading is_trading;
        dbn_normalized::is_quoting is_quoting;
        dbn_normalized::is_short_sell_restricted is_short_sell_restricted;
        dbn_normalized::reserved_7 reserved_7;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::status, {}, {}, {}};

    fields_type fields;

    // parse method
    static status_msg* parse(std::byte* buffer) {
        return reinterpret_cast<status_msg*>(buffer);
    }

    // parse method const
    static const status_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const status_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(status_msg::fields_type, ts_recv) == 0, "unexpected offset of status_msg::fields_type::ts_recv");
static_assert(offsetof(status_msg::fields_type, status_action) == 8, "unexpected offset of status_msg::fields_type::status_action");
static_assert(offsetof(status_msg::fields_type, status_reason) == 10, "unexpected offset of status_msg::fields_type::status_reason");
static_assert(offsetof(status_msg::fields_type, trading_event) == 12, "unexpected offset of status_msg::fields_type::trading_event");
static_assert(offsetof(status_msg::fields_type, is_trading) == 14, "unexpected offset of status_msg::fields_type::is_trading");
static_assert(offsetof(status_msg::fields_type, is_quoting) == 15, "unexpected offset of status_msg::fields_type::is_quoting");
static_assert(offsetof(status_msg::fields_type, is_short_sell_restricted) == 16, "unexpected offset of status_msg::fields_type::is_short_sell_restricted");
static_assert(offsetof(status_msg::fields_type, reserved_7) == 17, "unexpected offset of status_msg::fields_type::reserved_7");
static_assert(sizeof(status_msg::fields_type) == 24, "unexpected sizeof status_msg::fields_type");
static_assert(sizeof(status_msg) == sizeof(dbn_normalized::record_header) + 24, "unexpected sizeof status_msg");

#pragma pack(pop)
}
