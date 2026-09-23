#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ModifyFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OrderIdReference.hpp"
#include "../types/SizeType.hpp"
#include "../types/Price.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_06;

#pragma pack(push, 1)

// Order Modify Message
struct order_modify_message {

    struct fields_type {
        snap_deepplus::modify_flags modify_flags;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
        snap_deepplus::order_id_reference order_id_reference;
        snap_deepplus::size_type size;
        snap_deepplus::price price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deepplus::iex_tp_header iex_tp_header;
    snap_deepplus::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deepplus::iex_tp_message_length iex_tp_message_length;
    snap_deepplus::iex_tp_message_type iex_tp_message_type = snap_deepplus::iex_tp_message_type::enum_type::order_modify_message;

    fields_type fields;

    // parse method
    static order_modify_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_modify_message*>(buffer);
    }

    // parse method const
    static const order_modify_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_modify_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_modify_message::fields_type, modify_flags) == 0, "unexpected offset of order_modify_message::fields_type::modify_flags");
static_assert(offsetof(order_modify_message::fields_type, timestamp) == 1, "unexpected offset of order_modify_message::fields_type::timestamp");
static_assert(offsetof(order_modify_message::fields_type, symbol) == 9, "unexpected offset of order_modify_message::fields_type::symbol");
static_assert(offsetof(order_modify_message::fields_type, order_id_reference) == 17, "unexpected offset of order_modify_message::fields_type::order_id_reference");
static_assert(offsetof(order_modify_message::fields_type, size) == 25, "unexpected offset of order_modify_message::fields_type::size");
static_assert(offsetof(order_modify_message::fields_type, price) == 29, "unexpected offset of order_modify_message::fields_type::price");
static_assert(sizeof(order_modify_message::fields_type) == 37, "unexpected sizeof order_modify_message::fields_type");
static_assert(sizeof(order_modify_message) == sizeof(message_header) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) + 37, "unexpected sizeof order_modify_message");

#pragma pack(pop)
}
