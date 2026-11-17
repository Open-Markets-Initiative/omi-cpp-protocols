// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/WideComplexDoubleSidedTopOfMarketMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../structs/WideBid.hpp"
#include "../structs/WideOffer.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Wide Complex Double Sided Top Of Market Message
struct wide_complex_double_sided_top_of_market_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::strategy_id strategy_id;
        mach_complextopofmarket::wide_bid wide_bid;
        mach_complextopofmarket::wide_offer wide_offer;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::wide_complex_double_sided_top_of_market_message;

    fields_type fields;

    // parse method
    static wide_complex_double_sided_top_of_market_message* parse(std::byte* buffer) {
        return reinterpret_cast<wide_complex_double_sided_top_of_market_message*>(buffer);
    }

    // parse method const
    static const wide_complex_double_sided_top_of_market_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const wide_complex_double_sided_top_of_market_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(wide_complex_double_sided_top_of_market_message::fields_type, nanoseconds) == 0, "unexpected offset of wide_complex_double_sided_top_of_market_message::fields_type::nanoseconds");
static_assert(offsetof(wide_complex_double_sided_top_of_market_message::fields_type, strategy_id) == 4, "unexpected offset of wide_complex_double_sided_top_of_market_message::fields_type::strategy_id");
static_assert(offsetof(wide_complex_double_sided_top_of_market_message::fields_type, wide_bid) == 8, "unexpected offset of wide_complex_double_sided_top_of_market_message::fields_type::wide_bid");
static_assert(offsetof(wide_complex_double_sided_top_of_market_message::fields_type, wide_offer) == 25, "unexpected offset of wide_complex_double_sided_top_of_market_message::fields_type::wide_offer");
static_assert(sizeof(wide_complex_double_sided_top_of_market_message::fields_type) == 42, "unexpected sizeof wide_complex_double_sided_top_of_market_message::fields_type");
static_assert(sizeof(wide_complex_double_sided_top_of_market_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 42, "unexpected sizeof wide_complex_double_sided_top_of_market_message");

#pragma pack(pop)
}
