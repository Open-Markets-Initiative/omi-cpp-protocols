#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/OrderExecutionFlags.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Order Execution Message
struct order_execution_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::order_id order_id;
        mach_depthofmarket::trade_id trade_id;
        mach_depthofmarket::price price;
        mach_depthofmarket::size_type size;
        mach_depthofmarket::order_execution_flags order_execution_flags;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::order_execution_message;

    fields_type fields;

    // parse method
    static order_execution_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_execution_message*>(buffer);
    }

    // parse method const
    static const order_execution_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_execution_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_execution_message::fields_type, nanoseconds) == 0, "unexpected offset of order_execution_message::fields_type::nanoseconds");
static_assert(offsetof(order_execution_message::fields_type, symbol_id) == 4, "unexpected offset of order_execution_message::fields_type::symbol_id");
static_assert(offsetof(order_execution_message::fields_type, order_id) == 8, "unexpected offset of order_execution_message::fields_type::order_id");
static_assert(offsetof(order_execution_message::fields_type, trade_id) == 16, "unexpected offset of order_execution_message::fields_type::trade_id");
static_assert(offsetof(order_execution_message::fields_type, price) == 24, "unexpected offset of order_execution_message::fields_type::price");
static_assert(offsetof(order_execution_message::fields_type, size) == 32, "unexpected offset of order_execution_message::fields_type::size");
static_assert(offsetof(order_execution_message::fields_type, order_execution_flags) == 36, "unexpected offset of order_execution_message::fields_type::order_execution_flags");
static_assert(sizeof(order_execution_message::fields_type) == 37, "unexpected sizeof order_execution_message::fields_type");
static_assert(sizeof(order_execution_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 37, "unexpected sizeof order_execution_message");

#pragma pack(pop)
}
