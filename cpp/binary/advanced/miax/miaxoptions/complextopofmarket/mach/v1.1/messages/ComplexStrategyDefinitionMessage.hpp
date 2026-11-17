// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/ComplexStrategyDefinitionMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/ActiveOnMiax.hpp"
#include "../types/Reserved1.hpp"
#include "../types/UpdateReason.hpp"
#include "../types/Reserved10.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../types/ProductId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Reserved8.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)
struct complex_strategy_definition_message_leg_definition_entry {
    mach_complextopofmarket::product_id product_id;
    mach_complextopofmarket::leg_ratio_qty leg_ratio_qty;
    mach_complextopofmarket::leg_side leg_side;
    mach_complextopofmarket::reserved_8 reserved_8;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Strategy Definition Message
struct complex_strategy_definition_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::strategy_id strategy_id;
        mach_complextopofmarket::underlying_symbol underlying_symbol;
        mach_complextopofmarket::active_on_miax active_on_miax;
        mach_complextopofmarket::reserved_1 reserved_1;
        mach_complextopofmarket::update_reason update_reason;
        mach_complextopofmarket::reserved_10 reserved_10;
        mach_complextopofmarket::number_of_legs number_of_legs;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::complex_strategy_definition_message;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(mach_complextopofmarket::mach_packet_header) - sizeof(fields_type) - sizeof(mach_complextopofmarket::message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return sz == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(mach_complextopofmarket::mach_packet_header) - sizeof(fields_type) - sizeof(mach_complextopofmarket::message_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_strategy_definition_message_leg_definition_entry> leg_definition() const {
        return { tail_begin(), fields.number_of_legs.get().value(), tail_end() };
    }


    // parse method
    static complex_strategy_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_strategy_definition_message*>(buffer);
    }

    // parse method const
    static const complex_strategy_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_strategy_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_strategy_definition_message::fields_type, nanoseconds) == 0, "unexpected offset of complex_strategy_definition_message::fields_type::nanoseconds");
static_assert(offsetof(complex_strategy_definition_message::fields_type, strategy_id) == 4, "unexpected offset of complex_strategy_definition_message::fields_type::strategy_id");
static_assert(offsetof(complex_strategy_definition_message::fields_type, underlying_symbol) == 8, "unexpected offset of complex_strategy_definition_message::fields_type::underlying_symbol");
static_assert(offsetof(complex_strategy_definition_message::fields_type, active_on_miax) == 19, "unexpected offset of complex_strategy_definition_message::fields_type::active_on_miax");
static_assert(offsetof(complex_strategy_definition_message::fields_type, reserved_1) == 20, "unexpected offset of complex_strategy_definition_message::fields_type::reserved_1");
static_assert(offsetof(complex_strategy_definition_message::fields_type, update_reason) == 21, "unexpected offset of complex_strategy_definition_message::fields_type::update_reason");
static_assert(offsetof(complex_strategy_definition_message::fields_type, reserved_10) == 22, "unexpected offset of complex_strategy_definition_message::fields_type::reserved_10");
static_assert(offsetof(complex_strategy_definition_message::fields_type, number_of_legs) == 32, "unexpected offset of complex_strategy_definition_message::fields_type::number_of_legs");
static_assert(sizeof(complex_strategy_definition_message::fields_type) == 33, "unexpected sizeof complex_strategy_definition_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexStrategyDefinitionMessageWriter.hpp"
#include "details/ComplexStrategyDefinitionMessageReader.hpp"
