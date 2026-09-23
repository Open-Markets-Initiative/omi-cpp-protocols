#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/RetailLiquidityIndicator.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/IexTpHeader.hpp"
#include "../types/IexTpMessageBlockLength.hpp"
#include "../types/IexTpMessageLength.hpp"
#include "../types/IexTpMessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_06;

#pragma pack(push, 1)

// Retail Liquidity Indicator Message
struct retail_liquidity_indicator_message {

    struct fields_type {
        snap_deepplus::retail_liquidity_indicator retail_liquidity_indicator;
        snap_deepplus::timestamp timestamp;
        snap_deepplus::symbol symbol;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) - 2), message_type::enum_type::snapshot_data_message};
    snap_deepplus::iex_tp_header iex_tp_header;
    snap_deepplus::iex_tp_message_block_length iex_tp_message_block_length;
    snap_deepplus::iex_tp_message_length iex_tp_message_length;
    snap_deepplus::iex_tp_message_type iex_tp_message_type = snap_deepplus::iex_tp_message_type::enum_type::retail_liquidity_indicator_message;

    fields_type fields;

    // parse method
    static retail_liquidity_indicator_message* parse(std::byte* buffer) {
        return reinterpret_cast<retail_liquidity_indicator_message*>(buffer);
    }

    // parse method const
    static const retail_liquidity_indicator_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const retail_liquidity_indicator_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(retail_liquidity_indicator_message::fields_type, retail_liquidity_indicator) == 0, "unexpected offset of retail_liquidity_indicator_message::fields_type::retail_liquidity_indicator");
static_assert(offsetof(retail_liquidity_indicator_message::fields_type, timestamp) == 1, "unexpected offset of retail_liquidity_indicator_message::fields_type::timestamp");
static_assert(offsetof(retail_liquidity_indicator_message::fields_type, symbol) == 9, "unexpected offset of retail_liquidity_indicator_message::fields_type::symbol");
static_assert(sizeof(retail_liquidity_indicator_message::fields_type) == 17, "unexpected sizeof retail_liquidity_indicator_message::fields_type");
static_assert(sizeof(retail_liquidity_indicator_message) == sizeof(message_header) + sizeof(snap_deepplus::iex_tp_header) + sizeof(snap_deepplus::iex_tp_message_block_length) + sizeof(snap_deepplus::iex_tp_message_length) + sizeof(snap_deepplus::iex_tp_message_type) + 17, "unexpected sizeof retail_liquidity_indicator_message");

#pragma pack(pop)
}
