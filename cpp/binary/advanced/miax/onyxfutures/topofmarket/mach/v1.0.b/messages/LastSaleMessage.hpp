// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/LastSaleMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// Last Sale Message
struct last_sale_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::instrument_id instrument_id;
        mach_topofmarket::trade_id trade_id;
        mach_topofmarket::price price;
        mach_topofmarket::size_type size;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::last_sale_message;

    fields_type fields;

    // parse method
    static last_sale_message* parse(std::byte* buffer) {
        return reinterpret_cast<last_sale_message*>(buffer);
    }

    // parse method const
    static const last_sale_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const last_sale_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(last_sale_message::fields_type, timestamp) == 0, "unexpected offset of last_sale_message::fields_type::timestamp");
static_assert(offsetof(last_sale_message::fields_type, instrument_id) == 8, "unexpected offset of last_sale_message::fields_type::instrument_id");
static_assert(offsetof(last_sale_message::fields_type, trade_id) == 12, "unexpected offset of last_sale_message::fields_type::trade_id");
static_assert(offsetof(last_sale_message::fields_type, price) == 20, "unexpected offset of last_sale_message::fields_type::price");
static_assert(offsetof(last_sale_message::fields_type, size) == 28, "unexpected offset of last_sale_message::fields_type::size");
static_assert(sizeof(last_sale_message::fields_type) == 32, "unexpected sizeof last_sale_message::fields_type");
static_assert(sizeof(last_sale_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 32, "unexpected sizeof last_sale_message");

#pragma pack(pop)
}
