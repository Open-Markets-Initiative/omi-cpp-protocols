#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

#pragma pack(push, 1)

// Security Status
struct security_status {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::security_group security_group;
        sbe_mdp3::asset asset;
        sbe_mdp3::security_id_optional security_id_optional;
        sbe_mdp3::trade_date trade_date;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::security_trading_status security_trading_status;
        sbe_mdp3::halt_reason halt_reason;
        sbe_mdp3::security_trading_event security_trading_event;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::security_status, schema_id::enum_type::mktdata, version(8)};

    fields_type fields;

    // parse method
    static security_status* parse(std::byte* buffer) {
        return reinterpret_cast<security_status*>(buffer);
    }

    // parse method const
    static const security_status* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_status::fields_type, transact_time) == 0, "unexpected offset of security_status::fields_type::transact_time");
static_assert(offsetof(security_status::fields_type, security_group) == 8, "unexpected offset of security_status::fields_type::security_group");
static_assert(offsetof(security_status::fields_type, asset) == 14, "unexpected offset of security_status::fields_type::asset");
static_assert(offsetof(security_status::fields_type, security_id_optional) == 20, "unexpected offset of security_status::fields_type::security_id_optional");
static_assert(offsetof(security_status::fields_type, trade_date) == 24, "unexpected offset of security_status::fields_type::trade_date");
static_assert(offsetof(security_status::fields_type, match_event_indicator) == 26, "unexpected offset of security_status::fields_type::match_event_indicator");
static_assert(offsetof(security_status::fields_type, security_trading_status) == 27, "unexpected offset of security_status::fields_type::security_trading_status");
static_assert(offsetof(security_status::fields_type, halt_reason) == 28, "unexpected offset of security_status::fields_type::halt_reason");
static_assert(offsetof(security_status::fields_type, security_trading_event) == 29, "unexpected offset of security_status::fields_type::security_trading_event");
static_assert(sizeof(security_status::fields_type) == 30, "unexpected sizeof security_status::fields_type");
static_assert(sizeof(security_status) == sizeof(sbe_mdp3::message_size) + sizeof(sbe_mdp3::message_header) + 30, "unexpected sizeof security_status");

#pragma pack(pop)
}
