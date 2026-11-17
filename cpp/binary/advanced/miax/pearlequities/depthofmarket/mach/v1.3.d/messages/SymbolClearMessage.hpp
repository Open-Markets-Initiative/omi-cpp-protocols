// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SymbolClearMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Symbol Clear Message
struct symbol_clear_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
    };

    mach_depthofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_depthofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_depthofmarket::message_type)), mach_packet_type::enum_type::application_message, {}};
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::symbol_clear_message;

    fields_type fields;

    // parse method
    static symbol_clear_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_clear_message*>(buffer);
    }

    // parse method const
    static const symbol_clear_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_clear_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_clear_message::fields_type, nanoseconds) == 0, "unexpected offset of symbol_clear_message::fields_type::nanoseconds");
static_assert(offsetof(symbol_clear_message::fields_type, symbol_id) == 4, "unexpected offset of symbol_clear_message::fields_type::symbol_id");
static_assert(sizeof(symbol_clear_message::fields_type) == 8, "unexpected sizeof symbol_clear_message::fields_type");
static_assert(sizeof(symbol_clear_message) == sizeof(mach_depthofmarket::mach_packet_header) + sizeof(mach_depthofmarket::message_type) + 8, "unexpected sizeof symbol_clear_message");

#pragma pack(pop)
}
