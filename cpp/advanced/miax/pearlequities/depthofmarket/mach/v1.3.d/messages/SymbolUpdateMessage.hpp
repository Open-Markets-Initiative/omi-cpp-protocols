#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TickerSymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/TestSecurityIndicator.hpp"
#include "../types/SecondReserved1.hpp"
#include "../types/LotSize.hpp"
#include "../types/OpeningTime.hpp"
#include "../types/ClosingTime.hpp"
#include "../types/PrimaryMarketCode.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Symbol Update Message
struct symbol_update_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::symbol_id symbol_id;
        mach_depthofmarket::ticker_symbol ticker_symbol;
        mach_depthofmarket::reserved_1 reserved_1;
        mach_depthofmarket::test_security_indicator test_security_indicator;
        mach_depthofmarket::second_reserved_1 second_reserved_1;
        mach_depthofmarket::lot_size lot_size;
        mach_depthofmarket::opening_time opening_time;
        mach_depthofmarket::closing_time closing_time;
        mach_depthofmarket::primary_market_code primary_market_code;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::symbol_update_message;

    fields_type fields;

    // parse method
    static symbol_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_update_message*>(buffer);
    }

    // parse method const
    static const symbol_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_update_message::fields_type, nanoseconds) == 0, "unexpected offset of symbol_update_message::fields_type::nanoseconds");
static_assert(offsetof(symbol_update_message::fields_type, symbol_id) == 4, "unexpected offset of symbol_update_message::fields_type::symbol_id");
static_assert(offsetof(symbol_update_message::fields_type, ticker_symbol) == 8, "unexpected offset of symbol_update_message::fields_type::ticker_symbol");
static_assert(offsetof(symbol_update_message::fields_type, reserved_1) == 19, "unexpected offset of symbol_update_message::fields_type::reserved_1");
static_assert(offsetof(symbol_update_message::fields_type, test_security_indicator) == 20, "unexpected offset of symbol_update_message::fields_type::test_security_indicator");
static_assert(offsetof(symbol_update_message::fields_type, second_reserved_1) == 21, "unexpected offset of symbol_update_message::fields_type::second_reserved_1");
static_assert(offsetof(symbol_update_message::fields_type, lot_size) == 22, "unexpected offset of symbol_update_message::fields_type::lot_size");
static_assert(offsetof(symbol_update_message::fields_type, opening_time) == 24, "unexpected offset of symbol_update_message::fields_type::opening_time");
static_assert(offsetof(symbol_update_message::fields_type, closing_time) == 32, "unexpected offset of symbol_update_message::fields_type::closing_time");
static_assert(offsetof(symbol_update_message::fields_type, primary_market_code) == 40, "unexpected offset of symbol_update_message::fields_type::primary_market_code");
static_assert(sizeof(symbol_update_message::fields_type) == 41, "unexpected sizeof symbol_update_message::fields_type");
static_assert(sizeof(symbol_update_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 41, "unexpected sizeof symbol_update_message");

#pragma pack(pop)
}
