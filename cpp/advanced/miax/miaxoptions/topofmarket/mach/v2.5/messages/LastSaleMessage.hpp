#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/TradeId.hpp"
#include "../types/CorrectionNumber.hpp"
#include "../types/ReferenceTradeId.hpp"
#include "../types/ReferenceCorrectionNumber.hpp"
#include "../types/TradePrice.hpp"
#include "../types/TradeSize.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// Last Sale Message
struct last_sale_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::product_id product_id;
        mach_topofmarket::trade_id trade_id;
        mach_topofmarket::correction_number correction_number;
        mach_topofmarket::reference_trade_id reference_trade_id;
        mach_topofmarket::reference_correction_number reference_correction_number;
        mach_topofmarket::trade_price trade_price;
        mach_topofmarket::trade_size trade_size;
        mach_topofmarket::trade_condition trade_condition;
    };

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
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
static_assert(offsetof(last_sale_message::fields_type, nanoseconds) == 0, "unexpected offset of last_sale_message::fields_type::nanoseconds");
static_assert(offsetof(last_sale_message::fields_type, product_id) == 4, "unexpected offset of last_sale_message::fields_type::product_id");
static_assert(offsetof(last_sale_message::fields_type, trade_id) == 8, "unexpected offset of last_sale_message::fields_type::trade_id");
static_assert(offsetof(last_sale_message::fields_type, correction_number) == 12, "unexpected offset of last_sale_message::fields_type::correction_number");
static_assert(offsetof(last_sale_message::fields_type, reference_trade_id) == 13, "unexpected offset of last_sale_message::fields_type::reference_trade_id");
static_assert(offsetof(last_sale_message::fields_type, reference_correction_number) == 17, "unexpected offset of last_sale_message::fields_type::reference_correction_number");
static_assert(offsetof(last_sale_message::fields_type, trade_price) == 18, "unexpected offset of last_sale_message::fields_type::trade_price");
static_assert(offsetof(last_sale_message::fields_type, trade_size) == 22, "unexpected offset of last_sale_message::fields_type::trade_size");
static_assert(offsetof(last_sale_message::fields_type, trade_condition) == 26, "unexpected offset of last_sale_message::fields_type::trade_condition");
static_assert(sizeof(last_sale_message::fields_type) == 27, "unexpected sizeof last_sale_message::fields_type");
static_assert(sizeof(last_sale_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 27, "unexpected sizeof last_sale_message");

#pragma pack(pop)
}
