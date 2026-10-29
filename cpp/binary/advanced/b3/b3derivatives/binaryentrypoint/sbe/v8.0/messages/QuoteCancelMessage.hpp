#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


#pragma pack(push, 1)

// Quote Cancel Message
struct quote_cancel_message {

    struct fields_type {
        sbe_binaryentrypoint::bidirectional_business_header bidirectional_business_header;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::quote_id_optional quote_id_optional;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader executing_trader;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header));
    }

    // sequential access to variable-length regions
    sbe_var_data quote_req_id() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data desk_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static quote_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_cancel_message*>(buffer);
    }

    // parse method const
    static const quote_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_cancel_message::fields_type, bidirectional_business_header) == 0, "unexpected offset of quote_cancel_message::fields_type::bidirectional_business_header");
static_assert(offsetof(quote_cancel_message::fields_type, security_id) == 19, "unexpected offset of quote_cancel_message::fields_type::security_id");
static_assert(offsetof(quote_cancel_message::fields_type, quote_id_optional) == 27, "unexpected offset of quote_cancel_message::fields_type::quote_id_optional");
static_assert(offsetof(quote_cancel_message::fields_type, account) == 35, "unexpected offset of quote_cancel_message::fields_type::account");
static_assert(offsetof(quote_cancel_message::fields_type, sender_location) == 39, "unexpected offset of quote_cancel_message::fields_type::sender_location");
static_assert(offsetof(quote_cancel_message::fields_type, entering_trader) == 49, "unexpected offset of quote_cancel_message::fields_type::entering_trader");
static_assert(offsetof(quote_cancel_message::fields_type, executing_trader) == 54, "unexpected offset of quote_cancel_message::fields_type::executing_trader");
static_assert(sizeof(quote_cancel_message::fields_type) == 59, "unexpected sizeof quote_cancel_message::fields_type");

#pragma pack(pop)
}

#include "details/QuoteCancelMessageWriter.hpp"
#include "details/QuoteCancelMessageReader.hpp"
