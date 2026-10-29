#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/OnbehalfFirm.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


#pragma pack(push, 1)

// Negotiate Message
struct negotiate_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::timestamp timestamp;
        sbe_binaryentrypoint::entering_firm entering_firm;
        sbe_binaryentrypoint::onbehalf_firm onbehalf_firm;
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
    sbe_var_data credentials() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data client_ip(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data client_app_name(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data client_app_version(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static negotiate_message* parse(std::byte* buffer) {
        return reinterpret_cast<negotiate_message*>(buffer);
    }

    // parse method const
    static const negotiate_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const negotiate_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(negotiate_message::fields_type, session_id) == 0, "unexpected offset of negotiate_message::fields_type::session_id");
static_assert(offsetof(negotiate_message::fields_type, session_ver_id) == 4, "unexpected offset of negotiate_message::fields_type::session_ver_id");
static_assert(offsetof(negotiate_message::fields_type, timestamp) == 12, "unexpected offset of negotiate_message::fields_type::timestamp");
static_assert(offsetof(negotiate_message::fields_type, entering_firm) == 20, "unexpected offset of negotiate_message::fields_type::entering_firm");
static_assert(offsetof(negotiate_message::fields_type, onbehalf_firm) == 24, "unexpected offset of negotiate_message::fields_type::onbehalf_firm");
static_assert(sizeof(negotiate_message::fields_type) == 28, "unexpected sizeof negotiate_message::fields_type");

#pragma pack(pop)
}

#include "details/NegotiateMessageWriter.hpp"
#include "details/NegotiateMessageReader.hpp"
