// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/WideComplexTopOfMarketOfferMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/StrategyId.hpp"
#include "../types/WidePrice.hpp"
#include "../types/WideSize.hpp"
#include "../types/Reserved4.hpp"
#include "../types/TopOfMarketQuoteCondition.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// Wide Complex Top Of Market Offer Message
struct wide_complex_top_of_market_offer_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::strategy_id strategy_id;
        mach_complextopofmarket::wide_price wide_price;
        mach_complextopofmarket::wide_size wide_size;
        mach_complextopofmarket::reserved_4 reserved_4;
        mach_complextopofmarket::top_of_market_quote_condition top_of_market_quote_condition;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::wide_complex_top_of_market_offer_message;

    fields_type fields;

    // parse method
    static wide_complex_top_of_market_offer_message* parse(std::byte* buffer) {
        return reinterpret_cast<wide_complex_top_of_market_offer_message*>(buffer);
    }

    // parse method const
    static const wide_complex_top_of_market_offer_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const wide_complex_top_of_market_offer_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, nanoseconds) == 0, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::nanoseconds");
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, strategy_id) == 4, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::strategy_id");
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, wide_price) == 8, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::wide_price");
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, wide_size) == 16, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::wide_size");
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, reserved_4) == 20, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::reserved_4");
static_assert(offsetof(wide_complex_top_of_market_offer_message::fields_type, top_of_market_quote_condition) == 24, "unexpected offset of wide_complex_top_of_market_offer_message::fields_type::top_of_market_quote_condition");
static_assert(sizeof(wide_complex_top_of_market_offer_message::fields_type) == 25, "unexpected sizeof wide_complex_top_of_market_offer_message::fields_type");
static_assert(sizeof(wide_complex_top_of_market_offer_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 25, "unexpected sizeof wide_complex_top_of_market_offer_message");

#pragma pack(pop)
}
