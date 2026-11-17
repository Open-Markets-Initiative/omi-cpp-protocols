// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/TradeCancelMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TradeDate.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/Price.hpp"
#include "../types/SizeType.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// Trade Cancel Message
struct trade_cancel_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::trade_date trade_date;
        mach_topofmarket::instrument_id instrument_id;
        mach_topofmarket::trade_id trade_id;
        mach_topofmarket::correction_number correction_number;
        mach_topofmarket::price price;
        mach_topofmarket::size_type size;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::trade_cancel_message;

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
static_assert(offsetof(trade_cancel_message::fields_type, timestamp) == 0, "unexpected offset of trade_cancel_message::fields_type::timestamp");
static_assert(offsetof(trade_cancel_message::fields_type, trade_date) == 8, "unexpected offset of trade_cancel_message::fields_type::trade_date");
static_assert(offsetof(trade_cancel_message::fields_type, instrument_id) == 10, "unexpected offset of trade_cancel_message::fields_type::instrument_id");
static_assert(offsetof(trade_cancel_message::fields_type, trade_id) == 14, "unexpected offset of trade_cancel_message::fields_type::trade_id");
static_assert(offsetof(trade_cancel_message::fields_type, correction_number) == 22, "unexpected offset of trade_cancel_message::fields_type::correction_number");
static_assert(offsetof(trade_cancel_message::fields_type, price) == 23, "unexpected offset of trade_cancel_message::fields_type::price");
static_assert(offsetof(trade_cancel_message::fields_type, size) == 31, "unexpected offset of trade_cancel_message::fields_type::size");
static_assert(sizeof(trade_cancel_message::fields_type) == 35, "unexpected sizeof trade_cancel_message::fields_type");
static_assert(sizeof(trade_cancel_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 35, "unexpected sizeof trade_cancel_message");

#pragma pack(pop)
}
