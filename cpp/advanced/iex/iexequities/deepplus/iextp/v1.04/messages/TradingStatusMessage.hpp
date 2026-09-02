#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reason.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_04;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        iextp_deepplus::trading_status trading_status;
        iextp_deepplus::timestamp timestamp;
        iextp_deepplus::symbol symbol;
        iextp_deepplus::reason reason;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::trading_status_message};

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, trading_status) == 0, "unexpected offset of trading_status_message::fields_type::trading_status");
static_assert(offsetof(trading_status_message::fields_type, timestamp) == 1, "unexpected offset of trading_status_message::fields_type::timestamp");
static_assert(offsetof(trading_status_message::fields_type, symbol) == 9, "unexpected offset of trading_status_message::fields_type::symbol");
static_assert(offsetof(trading_status_message::fields_type, reason) == 17, "unexpected offset of trading_status_message::fields_type::reason");
static_assert(sizeof(trading_status_message::fields_type) == 21, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(message_header) + 21, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
