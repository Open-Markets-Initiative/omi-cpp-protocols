#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/PriceType.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OfficialPrice.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

#pragma pack(push, 1)

// Official Price Message
struct official_price_message {

    struct fields_type {
        snap_tops::price_type price_type;
        snap_tops::timestamp timestamp;
        snap_tops::symbol symbol;
        snap_tops::official_price official_price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_tops::iex_tp_header) + sizeof(snap_tops::iex_tp_message_block_length) + sizeof(snap_tops::iex_tp_message_length) + sizeof(snap_tops::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_tops::iex_tp_header iex_tp_header;
    snap_tops::iex_tp_message_block_length iex_tp_message_block_length;
    snap_tops::iex_tp_message_length iex_tp_message_length;
    snap_tops::iex_tp_message_type iex_tp_message_type = snap_tops::iex_tp_message_type::enum_type::official_price_message;

    fields_type fields;

    // parse method
    static official_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<official_price_message*>(buffer);
    }

    // parse method const
    static const official_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const official_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(official_price_message::fields_type, price_type) == 0, "unexpected offset of official_price_message::fields_type::price_type");
static_assert(offsetof(official_price_message::fields_type, timestamp) == 1, "unexpected offset of official_price_message::fields_type::timestamp");
static_assert(offsetof(official_price_message::fields_type, symbol) == 9, "unexpected offset of official_price_message::fields_type::symbol");
static_assert(offsetof(official_price_message::fields_type, official_price) == 17, "unexpected offset of official_price_message::fields_type::official_price");
static_assert(sizeof(official_price_message::fields_type) == 25, "unexpected sizeof official_price_message::fields_type");
static_assert(sizeof(official_price_message) == sizeof(message_header) + sizeof(snap_tops::iex_tp_header) + sizeof(snap_tops::iex_tp_message_block_length) + sizeof(snap_tops::iex_tp_message_length) + sizeof(snap_tops::iex_tp_message_type) + 25, "unexpected sizeof official_price_message");

#pragma pack(pop)
}
