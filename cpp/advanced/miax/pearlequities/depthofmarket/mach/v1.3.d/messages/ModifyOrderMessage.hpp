#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/ModifyOrderFlags.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Modify Order Message
struct modify_order_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::order_id order_id;
        mach_depthofmarket::price price;
        mach_depthofmarket::size_type size;
        mach_depthofmarket::modify_order_flags modify_order_flags;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::modify_order_message;

    fields_type fields;

    // parse method
    static modify_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<modify_order_message*>(buffer);
    }

    // parse method const
    static const modify_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const modify_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(modify_order_message::fields_type, nanoseconds) == 0, "unexpected offset of modify_order_message::fields_type::nanoseconds");
static_assert(offsetof(modify_order_message::fields_type, symbol_id) == 4, "unexpected offset of modify_order_message::fields_type::symbol_id");
static_assert(offsetof(modify_order_message::fields_type, order_id) == 8, "unexpected offset of modify_order_message::fields_type::order_id");
static_assert(offsetof(modify_order_message::fields_type, price) == 16, "unexpected offset of modify_order_message::fields_type::price");
static_assert(offsetof(modify_order_message::fields_type, size) == 24, "unexpected offset of modify_order_message::fields_type::size");
static_assert(offsetof(modify_order_message::fields_type, modify_order_flags) == 28, "unexpected offset of modify_order_message::fields_type::modify_order_flags");
static_assert(sizeof(modify_order_message::fields_type) == 29, "unexpected sizeof modify_order_message::fields_type");
static_assert(sizeof(modify_order_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 29, "unexpected sizeof modify_order_message");

#pragma pack(pop)
}
