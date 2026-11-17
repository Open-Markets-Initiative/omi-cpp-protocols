// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/StrategyTradeMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/TradeId.hpp"
#include "../types/NetPrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Reserved16.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Strategy Trade Message
struct strategy_trade_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::strategy_id strategy_id;
        mach_complextopofmarket::trade_id trade_id;
        mach_complextopofmarket::net_price net_price;
        mach_complextopofmarket::trade_size trade_size;
        mach_complextopofmarket::trade_condition trade_condition;
        mach_complextopofmarket::reserved_16 reserved_16;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::strategy_trade_message;

    fields_type fields;

    // parse method
    static strategy_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<strategy_trade_message*>(buffer);
    }

    // parse method const
    static const strategy_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const strategy_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(strategy_trade_message::fields_type, nanoseconds) == 0, "unexpected offset of strategy_trade_message::fields_type::nanoseconds");
static_assert(offsetof(strategy_trade_message::fields_type, strategy_id) == 4, "unexpected offset of strategy_trade_message::fields_type::strategy_id");
static_assert(offsetof(strategy_trade_message::fields_type, trade_id) == 8, "unexpected offset of strategy_trade_message::fields_type::trade_id");
static_assert(offsetof(strategy_trade_message::fields_type, net_price) == 12, "unexpected offset of strategy_trade_message::fields_type::net_price");
static_assert(offsetof(strategy_trade_message::fields_type, trade_size) == 20, "unexpected offset of strategy_trade_message::fields_type::trade_size");
static_assert(offsetof(strategy_trade_message::fields_type, trade_condition) == 24, "unexpected offset of strategy_trade_message::fields_type::trade_condition");
static_assert(offsetof(strategy_trade_message::fields_type, reserved_16) == 25, "unexpected offset of strategy_trade_message::fields_type::reserved_16");
static_assert(sizeof(strategy_trade_message::fields_type) == 41, "unexpected sizeof strategy_trade_message::fields_type");
static_assert(sizeof(strategy_trade_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 41, "unexpected sizeof strategy_trade_message");

#pragma pack(pop)
}
