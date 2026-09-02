#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/RetailLiquidityIndicator.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

namespace iextp_deep = ::iex::iexequities::deep::iextp::v1_08;

#pragma pack(push, 1)

// Retail Liquidity Indicator Message
struct retail_liquidity_indicator_message {

    struct fields_type {
        iextp_deep::retail_liquidity_indicator retail_liquidity_indicator;
        iextp_deep::timestamp timestamp;
        iextp_deep::symbol symbol;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::retail_liquidity_indicator_message};

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
static_assert(sizeof(retail_liquidity_indicator_message) == sizeof(message_header) + 17, "unexpected sizeof retail_liquidity_indicator_message");

#pragma pack(pop)
}
