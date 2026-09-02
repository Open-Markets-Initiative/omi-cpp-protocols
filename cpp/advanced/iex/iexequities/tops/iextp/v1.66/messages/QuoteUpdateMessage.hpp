#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/QuoteUpdateFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/BidSize.hpp"
#include "../types/BidPrice.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskSize.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

namespace iextp_tops = ::iex::iexequities::tops::iextp::v1_66;

#pragma pack(push, 1)

// Quote Update Message
struct quote_update_message {

    struct fields_type {
        iextp_tops::quote_update_flags quote_update_flags;
        iextp_tops::timestamp timestamp;
        iextp_tops::symbol symbol;
        iextp_tops::bid_size bid_size;
        iextp_tops::bid_price bid_price;
        iextp_tops::ask_price ask_price;
        iextp_tops::ask_size ask_size;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::quote_update_message};

    fields_type fields;

    // parse method
    static quote_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_update_message*>(buffer);
    }

    // parse method const
    static const quote_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_update_message::fields_type, quote_update_flags) == 0, "unexpected offset of quote_update_message::fields_type::quote_update_flags");
static_assert(offsetof(quote_update_message::fields_type, timestamp) == 1, "unexpected offset of quote_update_message::fields_type::timestamp");
static_assert(offsetof(quote_update_message::fields_type, symbol) == 9, "unexpected offset of quote_update_message::fields_type::symbol");
static_assert(offsetof(quote_update_message::fields_type, bid_size) == 17, "unexpected offset of quote_update_message::fields_type::bid_size");
static_assert(offsetof(quote_update_message::fields_type, bid_price) == 21, "unexpected offset of quote_update_message::fields_type::bid_price");
static_assert(offsetof(quote_update_message::fields_type, ask_price) == 29, "unexpected offset of quote_update_message::fields_type::ask_price");
static_assert(offsetof(quote_update_message::fields_type, ask_size) == 37, "unexpected offset of quote_update_message::fields_type::ask_size");
static_assert(sizeof(quote_update_message::fields_type) == 41, "unexpected sizeof quote_update_message::fields_type");
static_assert(sizeof(quote_update_message) == sizeof(message_header) + 41, "unexpected sizeof quote_update_message");

#pragma pack(pop)
}
