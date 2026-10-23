#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeLinkId.hpp"
#include "../types/WorkupTradingStatus.hpp"
#include "../types/HaltReason.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/AggressorIndicator.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct security_status_workup_groups_entry {
    sbe_mdp3::order_id order_id;
    sbe_mdp3::side side;
    sbe_mdp3::aggressor_indicator aggressor_indicator;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Security Status Workup
struct security_status_workup {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::md_entry_px_optional_ex md_entry_px_optional_ex;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::trade_date trade_date;
        sbe_mdp3::trade_link_id trade_link_id;
        sbe_mdp3::workup_trading_status workup_trading_status;
        sbe_mdp3::halt_reason halt_reason;
        sbe_mdp3::security_trading_event security_trading_event;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::security_status_workup, schema_id::enum_type::mktdata, version(13)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<security_status_workup_groups_entry, group_size> security_status_workup_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static security_status_workup* parse(std::byte* buffer) {
        return reinterpret_cast<security_status_workup*>(buffer);
    }

    // parse method const
    static const security_status_workup* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status_workup*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_status_workup::fields_type, transact_time) == 0, "unexpected offset of security_status_workup::fields_type::transact_time");
static_assert(offsetof(security_status_workup::fields_type, md_entry_px_optional_ex) == 8, "unexpected offset of security_status_workup::fields_type::md_entry_px_optional_ex");
static_assert(offsetof(security_status_workup::fields_type, security_id) == 16, "unexpected offset of security_status_workup::fields_type::security_id");
static_assert(offsetof(security_status_workup::fields_type, match_event_indicator) == 20, "unexpected offset of security_status_workup::fields_type::match_event_indicator");
static_assert(offsetof(security_status_workup::fields_type, trade_date) == 21, "unexpected offset of security_status_workup::fields_type::trade_date");
static_assert(offsetof(security_status_workup::fields_type, trade_link_id) == 23, "unexpected offset of security_status_workup::fields_type::trade_link_id");
static_assert(offsetof(security_status_workup::fields_type, workup_trading_status) == 27, "unexpected offset of security_status_workup::fields_type::workup_trading_status");
static_assert(offsetof(security_status_workup::fields_type, halt_reason) == 28, "unexpected offset of security_status_workup::fields_type::halt_reason");
static_assert(offsetof(security_status_workup::fields_type, security_trading_event) == 29, "unexpected offset of security_status_workup::fields_type::security_trading_event");
static_assert(sizeof(security_status_workup::fields_type) == 30, "unexpected sizeof security_status_workup::fields_type");

#pragma pack(pop)
}

#include "details/SecurityStatusWorkupWriter.hpp"
#include "details/SecurityStatusWorkupReader.hpp"
