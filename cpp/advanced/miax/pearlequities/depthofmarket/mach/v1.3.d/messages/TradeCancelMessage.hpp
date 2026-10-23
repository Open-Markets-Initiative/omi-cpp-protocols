#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Trade Cancel Message
struct trade_cancel_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::trade_id trade_id;
        mach_depthofmarket::correction_number correction_number;
        mach_depthofmarket::price price;
        mach_depthofmarket::size_type size;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::trade_cancel_message;

    fields_type fields;

    // parse method
    static trade_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancel_message*>(buffer);
    }

    // parse method const
    static const trade_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancel_message::fields_type, nanoseconds) == 0, "unexpected offset of trade_cancel_message::fields_type::nanoseconds");
static_assert(offsetof(trade_cancel_message::fields_type, symbol_id) == 4, "unexpected offset of trade_cancel_message::fields_type::symbol_id");
static_assert(offsetof(trade_cancel_message::fields_type, trade_id) == 8, "unexpected offset of trade_cancel_message::fields_type::trade_id");
static_assert(offsetof(trade_cancel_message::fields_type, correction_number) == 16, "unexpected offset of trade_cancel_message::fields_type::correction_number");
static_assert(offsetof(trade_cancel_message::fields_type, price) == 17, "unexpected offset of trade_cancel_message::fields_type::price");
static_assert(offsetof(trade_cancel_message::fields_type, size) == 25, "unexpected offset of trade_cancel_message::fields_type::size");
static_assert(sizeof(trade_cancel_message::fields_type) == 29, "unexpected sizeof trade_cancel_message::fields_type");
static_assert(sizeof(trade_cancel_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 29, "unexpected sizeof trade_cancel_message");

#pragma pack(pop)
}
