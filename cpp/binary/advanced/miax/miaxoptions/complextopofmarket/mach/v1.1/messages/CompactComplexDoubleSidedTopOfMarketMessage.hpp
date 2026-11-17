// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/CompactComplexDoubleSidedTopOfMarketMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../structs/CompactBid.hpp"
#include "../structs/CompactOffer.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Compact Complex Double Sided Top Of Market Message
struct compact_complex_double_sided_top_of_market_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::strategy_id strategy_id;
        mach_complextopofmarket::compact_bid compact_bid;
        mach_complextopofmarket::compact_offer compact_offer;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::compact_complex_double_sided_top_of_market_message;

    fields_type fields;

    // parse method
    static compact_complex_double_sided_top_of_market_message* parse(std::byte* buffer) {
        return reinterpret_cast<compact_complex_double_sided_top_of_market_message*>(buffer);
    }

    // parse method const
    static const compact_complex_double_sided_top_of_market_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const compact_complex_double_sided_top_of_market_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(compact_complex_double_sided_top_of_market_message::fields_type, nanoseconds) == 0, "unexpected offset of compact_complex_double_sided_top_of_market_message::fields_type::nanoseconds");
static_assert(offsetof(compact_complex_double_sided_top_of_market_message::fields_type, strategy_id) == 4, "unexpected offset of compact_complex_double_sided_top_of_market_message::fields_type::strategy_id");
static_assert(offsetof(compact_complex_double_sided_top_of_market_message::fields_type, compact_bid) == 8, "unexpected offset of compact_complex_double_sided_top_of_market_message::fields_type::compact_bid");
static_assert(offsetof(compact_complex_double_sided_top_of_market_message::fields_type, compact_offer) == 15, "unexpected offset of compact_complex_double_sided_top_of_market_message::fields_type::compact_offer");
static_assert(sizeof(compact_complex_double_sided_top_of_market_message::fields_type) == 22, "unexpected sizeof compact_complex_double_sided_top_of_market_message::fields_type");
static_assert(sizeof(compact_complex_double_sided_top_of_market_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 22, "unexpected sizeof compact_complex_double_sided_top_of_market_message");

#pragma pack(pop)
}
