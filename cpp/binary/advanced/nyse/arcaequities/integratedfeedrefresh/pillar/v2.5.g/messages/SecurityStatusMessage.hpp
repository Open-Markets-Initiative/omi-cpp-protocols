#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/HaltCondition.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Price1.hpp"
#include "../types/Price2.hpp"
#include "../types/SsrTriggeringExchangeId.hpp"
#include "../types/SsrTriggeringVolume.hpp"
#include "../types/Time.hpp"
#include "../types/SsrState.hpp"
#include "../types/MarketState.hpp"
#include "../types/SessionState.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

namespace pillar_integratedfeedrefresh = ::nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g;

#pragma pack(push, 1)

// Security Status Message
struct security_status_message {

    struct fields_type {
        pillar_integratedfeedrefresh::source_time source_time;
        pillar_integratedfeedrefresh::source_time_ns source_time_ns;
        pillar_integratedfeedrefresh::symbol_index symbol_index;
        pillar_integratedfeedrefresh::symbol_seq_num symbol_seq_num;
        pillar_integratedfeedrefresh::security_status security_status;
        pillar_integratedfeedrefresh::halt_condition halt_condition;
        pillar_integratedfeedrefresh::reserved_4 reserved_4;
        pillar_integratedfeedrefresh::price_1 price_1;
        pillar_integratedfeedrefresh::price_2 price_2;
        pillar_integratedfeedrefresh::ssr_triggering_exchange_id ssr_triggering_exchange_id;
        pillar_integratedfeedrefresh::ssr_triggering_volume ssr_triggering_volume;
        pillar_integratedfeedrefresh::time time;
        pillar_integratedfeedrefresh::ssr_state ssr_state;
        pillar_integratedfeedrefresh::market_state market_state;
        pillar_integratedfeedrefresh::session_state session_state;
    };

    pillar_integratedfeedrefresh::message_header header = {std::uint16_t(sizeof(pillar_integratedfeedrefresh::message_header) + sizeof(fields_type)), message_type::enum_type::security_status_message};

    fields_type fields;

    // parse method
    static security_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_status_message*>(buffer);
    }

    // parse method const
    static const security_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_status_message::fields_type, source_time) == 0, "unexpected offset of security_status_message::fields_type::source_time");
static_assert(offsetof(security_status_message::fields_type, source_time_ns) == 4, "unexpected offset of security_status_message::fields_type::source_time_ns");
static_assert(offsetof(security_status_message::fields_type, symbol_index) == 8, "unexpected offset of security_status_message::fields_type::symbol_index");
static_assert(offsetof(security_status_message::fields_type, symbol_seq_num) == 12, "unexpected offset of security_status_message::fields_type::symbol_seq_num");
static_assert(offsetof(security_status_message::fields_type, security_status) == 16, "unexpected offset of security_status_message::fields_type::security_status");
static_assert(offsetof(security_status_message::fields_type, halt_condition) == 17, "unexpected offset of security_status_message::fields_type::halt_condition");
static_assert(offsetof(security_status_message::fields_type, reserved_4) == 18, "unexpected offset of security_status_message::fields_type::reserved_4");
static_assert(offsetof(security_status_message::fields_type, price_1) == 22, "unexpected offset of security_status_message::fields_type::price_1");
static_assert(offsetof(security_status_message::fields_type, price_2) == 26, "unexpected offset of security_status_message::fields_type::price_2");
static_assert(offsetof(security_status_message::fields_type, ssr_triggering_exchange_id) == 30, "unexpected offset of security_status_message::fields_type::ssr_triggering_exchange_id");
static_assert(offsetof(security_status_message::fields_type, ssr_triggering_volume) == 31, "unexpected offset of security_status_message::fields_type::ssr_triggering_volume");
static_assert(offsetof(security_status_message::fields_type, time) == 35, "unexpected offset of security_status_message::fields_type::time");
static_assert(offsetof(security_status_message::fields_type, ssr_state) == 39, "unexpected offset of security_status_message::fields_type::ssr_state");
static_assert(offsetof(security_status_message::fields_type, market_state) == 40, "unexpected offset of security_status_message::fields_type::market_state");
static_assert(offsetof(security_status_message::fields_type, session_state) == 41, "unexpected offset of security_status_message::fields_type::session_state");
static_assert(sizeof(security_status_message::fields_type) == 42, "unexpected sizeof security_status_message::fields_type");
static_assert(sizeof(security_status_message) == sizeof(pillar_integratedfeedrefresh::message_header) + 42, "unexpected sizeof security_status_message");

#pragma pack(pop)
}
