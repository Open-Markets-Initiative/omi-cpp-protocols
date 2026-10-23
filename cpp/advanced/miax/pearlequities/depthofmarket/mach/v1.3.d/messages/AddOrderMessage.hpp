#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderSide.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/AttributableId.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Add Order Message
struct add_order_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::order_id order_id;
        mach_depthofmarket::order_side order_side;
        mach_depthofmarket::price price;
        mach_depthofmarket::size_type size;
        mach_depthofmarket::attributable_id attributable_id;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::add_order_message;

    fields_type fields;

    // parse method
    static add_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_message*>(buffer);
    }

    // parse method const
    static const add_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_message::fields_type, nanoseconds) == 0, "unexpected offset of add_order_message::fields_type::nanoseconds");
static_assert(offsetof(add_order_message::fields_type, symbol_id) == 4, "unexpected offset of add_order_message::fields_type::symbol_id");
static_assert(offsetof(add_order_message::fields_type, order_id) == 8, "unexpected offset of add_order_message::fields_type::order_id");
static_assert(offsetof(add_order_message::fields_type, order_side) == 16, "unexpected offset of add_order_message::fields_type::order_side");
static_assert(offsetof(add_order_message::fields_type, price) == 17, "unexpected offset of add_order_message::fields_type::price");
static_assert(offsetof(add_order_message::fields_type, size) == 25, "unexpected offset of add_order_message::fields_type::size");
static_assert(offsetof(add_order_message::fields_type, attributable_id) == 29, "unexpected offset of add_order_message::fields_type::attributable_id");
static_assert(sizeof(add_order_message::fields_type) == 33, "unexpected sizeof add_order_message::fields_type");
static_assert(sizeof(add_order_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 33, "unexpected sizeof add_order_message");

#pragma pack(pop)
}
