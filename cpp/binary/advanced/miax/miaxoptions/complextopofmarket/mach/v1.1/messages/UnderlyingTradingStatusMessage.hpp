// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/UnderlyingTradingStatusMessage.hpp
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

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Underlying Trading Status Message
struct underlying_trading_status_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::underlying_symbol underlying_symbol;
        mach_complextopofmarket::trading_status trading_status;
        mach_complextopofmarket::event_reason event_reason;
        mach_complextopofmarket::expected_event_time_seconds_part expected_event_time_seconds_part;
        mach_complextopofmarket::expected_event_time_nano_seconds_part expected_event_time_nano_seconds_part;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::underlying_trading_status_message;

    fields_type fields;

    // parse method
    static underlying_trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<underlying_trading_status_message*>(buffer);
    }

    // parse method const
    static const underlying_trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const underlying_trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(underlying_trading_status_message::fields_type, nanoseconds) == 0, "unexpected offset of underlying_trading_status_message::fields_type::nanoseconds");
static_assert(offsetof(underlying_trading_status_message::fields_type, underlying_symbol) == 4, "unexpected offset of underlying_trading_status_message::fields_type::underlying_symbol");
static_assert(offsetof(underlying_trading_status_message::fields_type, trading_status) == 15, "unexpected offset of underlying_trading_status_message::fields_type::trading_status");
static_assert(offsetof(underlying_trading_status_message::fields_type, event_reason) == 16, "unexpected offset of underlying_trading_status_message::fields_type::event_reason");
static_assert(offsetof(underlying_trading_status_message::fields_type, expected_event_time_seconds_part) == 17, "unexpected offset of underlying_trading_status_message::fields_type::expected_event_time_seconds_part");
static_assert(offsetof(underlying_trading_status_message::fields_type, expected_event_time_nano_seconds_part) == 21, "unexpected offset of underlying_trading_status_message::fields_type::expected_event_time_nano_seconds_part");
static_assert(sizeof(underlying_trading_status_message::fields_type) == 25, "unexpected sizeof underlying_trading_status_message::fields_type");
static_assert(sizeof(underlying_trading_status_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 25, "unexpected sizeof underlying_trading_status_message");

#pragma pack(pop)
}
