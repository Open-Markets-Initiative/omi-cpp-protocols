#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/PriceType.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/OfficialPrice.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

namespace iextp_tops = ::iex::iexequities::tops::iextp::v1_64;

#pragma pack(push, 1)

// Official Price Message
struct official_price_message {

    struct fields_type {
        iextp_tops::price_type price_type;
        iextp_tops::timestamp timestamp;
        iextp_tops::symbol symbol;
        iextp_tops::official_price official_price;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::official_price_message};

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
static_assert(sizeof(official_price_message) == sizeof(message_header) + 25, "unexpected sizeof official_price_message");

#pragma pack(pop)
}
