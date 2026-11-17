// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: messages/UnderlyingTradingStatusNotificationMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/EventReason.hpp"
#include "../types/ExpectedEventTimeSecondsPart.hpp"
#include "../types/ExpectedEventTimeNanoSecondsPart.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// Underlying Trading Status Notification Message
struct underlying_trading_status_notification_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::underlying_symbol underlying_symbol;
        mach_topofmarket::trading_status trading_status;
        mach_topofmarket::event_reason event_reason;
        mach_topofmarket::expected_event_time_seconds_part expected_event_time_seconds_part;
        mach_topofmarket::expected_event_time_nano_seconds_part expected_event_time_nano_seconds_part;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::underlying_trading_status_notification_message;

    fields_type fields;

    // parse method
    static underlying_trading_status_notification_message* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_trading_status_notification_message*>(buffer);
    }

    // parse method const
    static const underlying_trading_status_notification_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_trading_status_notification_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, nanoseconds) == 0, "unexpected offset of underlying_trading_status_notification_message::fields_type::nanoseconds");
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, underlying_symbol) == 4, "unexpected offset of underlying_trading_status_notification_message::fields_type::underlying_symbol");
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, trading_status) == 15, "unexpected offset of underlying_trading_status_notification_message::fields_type::trading_status");
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, event_reason) == 16, "unexpected offset of underlying_trading_status_notification_message::fields_type::event_reason");
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, expected_event_time_seconds_part) == 17, "unexpected offset of underlying_trading_status_notification_message::fields_type::expected_event_time_seconds_part");
static_assert(offsetof(underlying_trading_status_notification_message::fields_type, expected_event_time_nano_seconds_part) == 21, "unexpected offset of underlying_trading_status_notification_message::fields_type::expected_event_time_nano_seconds_part");
static_assert(sizeof(underlying_trading_status_notification_message::fields_type) == 25, "unexpected sizeof underlying_trading_status_notification_message::fields_type");
static_assert(sizeof(underlying_trading_status_notification_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 25, "unexpected sizeof underlying_trading_status_notification_message");

#pragma pack(pop)
}
