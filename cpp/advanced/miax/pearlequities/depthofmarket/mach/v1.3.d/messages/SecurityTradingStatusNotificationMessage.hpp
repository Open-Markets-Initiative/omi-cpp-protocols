#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/MarketState.hpp"
#include "../types/ShortSaleRestriction.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Security Trading Status Notification Message
struct security_trading_status_notification_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::trading_status trading_status;
        mach_depthofmarket::market_state market_state;
        mach_depthofmarket::short_sale_restriction short_sale_restriction;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::security_trading_status_notification_message;

    fields_type fields;

    // parse method
    static security_trading_status_notification_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_trading_status_notification_message*>(buffer);
    }

    // parse method const
    static const security_trading_status_notification_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_trading_status_notification_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_trading_status_notification_message::fields_type, nanoseconds) == 0, "unexpected offset of security_trading_status_notification_message::fields_type::nanoseconds");
static_assert(offsetof(security_trading_status_notification_message::fields_type, symbol_id) == 4, "unexpected offset of security_trading_status_notification_message::fields_type::symbol_id");
static_assert(offsetof(security_trading_status_notification_message::fields_type, trading_status) == 8, "unexpected offset of security_trading_status_notification_message::fields_type::trading_status");
static_assert(offsetof(security_trading_status_notification_message::fields_type, market_state) == 9, "unexpected offset of security_trading_status_notification_message::fields_type::market_state");
static_assert(offsetof(security_trading_status_notification_message::fields_type, short_sale_restriction) == 10, "unexpected offset of security_trading_status_notification_message::fields_type::short_sale_restriction");
static_assert(sizeof(security_trading_status_notification_message::fields_type) == 11, "unexpected sizeof security_trading_status_notification_message::fields_type");
static_assert(sizeof(security_trading_status_notification_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 11, "unexpected sizeof security_trading_status_notification_message");

#pragma pack(pop)
}
