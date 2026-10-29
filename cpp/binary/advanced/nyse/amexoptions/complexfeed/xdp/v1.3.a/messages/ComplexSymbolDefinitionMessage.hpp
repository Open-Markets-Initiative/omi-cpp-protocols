#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/ComplexSymbol.hpp"
#include "../types/ChannelId.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/Reserved1.hpp"
#include "../types/StreamId.hpp"
#include "../types/NoOfLegs.hpp"
#include "../types/Reserved2.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/Side.hpp"
#include "../types/LegSecurityType.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)
struct complex_symbol_definition_message_leg_definition_entry {
    xdp_complexfeed::symbol_index symbol_index;
    xdp_complexfeed::leg_ratio_qty leg_ratio_qty;
    xdp_complexfeed::side side;
    xdp_complexfeed::leg_security_type leg_security_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Symbol Definition Message
struct complex_symbol_definition_message {

    struct fields_type {
        xdp_complexfeed::complex_index complex_index;
        xdp_complexfeed::complex_symbol complex_symbol;
        xdp_complexfeed::channel_id channel_id;
        xdp_complexfeed::market_id market_id;
        xdp_complexfeed::system_id system_id;
        xdp_complexfeed::reserved_1 reserved_1;
        xdp_complexfeed::stream_id stream_id;
        xdp_complexfeed::no_of_legs no_of_legs;
        xdp_complexfeed::reserved_2 reserved_2;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_symbol_definition_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(xdp_complexfeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(xdp_complexfeed::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_symbol_definition_message_leg_definition_entry> leg_definition() const {
        return { tail_begin(), fields.no_of_legs.get().value(), tail_end() };
    }


    // parse method
    static complex_symbol_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_symbol_definition_message*>(buffer);
    }

    // parse method const
    static const complex_symbol_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_symbol_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_symbol_definition_message::fields_type, complex_index) == 0, "unexpected offset of complex_symbol_definition_message::fields_type::complex_index");
static_assert(offsetof(complex_symbol_definition_message::fields_type, complex_symbol) == 4, "unexpected offset of complex_symbol_definition_message::fields_type::complex_symbol");
static_assert(offsetof(complex_symbol_definition_message::fields_type, channel_id) == 25, "unexpected offset of complex_symbol_definition_message::fields_type::channel_id");
static_assert(offsetof(complex_symbol_definition_message::fields_type, market_id) == 26, "unexpected offset of complex_symbol_definition_message::fields_type::market_id");
static_assert(offsetof(complex_symbol_definition_message::fields_type, system_id) == 28, "unexpected offset of complex_symbol_definition_message::fields_type::system_id");
static_assert(offsetof(complex_symbol_definition_message::fields_type, reserved_1) == 29, "unexpected offset of complex_symbol_definition_message::fields_type::reserved_1");
static_assert(offsetof(complex_symbol_definition_message::fields_type, stream_id) == 30, "unexpected offset of complex_symbol_definition_message::fields_type::stream_id");
static_assert(offsetof(complex_symbol_definition_message::fields_type, no_of_legs) == 32, "unexpected offset of complex_symbol_definition_message::fields_type::no_of_legs");
static_assert(offsetof(complex_symbol_definition_message::fields_type, reserved_2) == 34, "unexpected offset of complex_symbol_definition_message::fields_type::reserved_2");
static_assert(sizeof(complex_symbol_definition_message::fields_type) == 36, "unexpected sizeof complex_symbol_definition_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexSymbolDefinitionMessageWriter.hpp"
#include "details/ComplexSymbolDefinitionMessageReader.hpp"
