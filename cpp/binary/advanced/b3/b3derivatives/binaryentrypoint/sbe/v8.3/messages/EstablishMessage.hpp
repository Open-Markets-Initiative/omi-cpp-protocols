#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SessionId.hpp"
#include "../types/SessionVerId.hpp"
#include "../types/Timestamp.hpp"
#include "../types/KeepAliveInterval.hpp"
#include "../types/NextSeqNo.hpp"
#include "../types/CancelOnDisconnectType.hpp"
#include "../types/Offset33Padding1.hpp"
#include "../types/CodTimeoutWindow.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// Establish Message
struct establish_message {

    struct fields_type {
        sbe_binaryentrypoint::session_id session_id;
        sbe_binaryentrypoint::session_ver_id session_ver_id;
        sbe_binaryentrypoint::timestamp timestamp;
        sbe_binaryentrypoint::keep_alive_interval keep_alive_interval;
        sbe_binaryentrypoint::next_seq_no next_seq_no;
        sbe_binaryentrypoint::cancel_on_disconnect_type cancel_on_disconnect_type;
        sbe_binaryentrypoint::offset_33_padding_1 offset_33_padding_1;
        sbe_binaryentrypoint::cod_timeout_window cod_timeout_window;
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


    // parse method
    static establish_message* parse(std::byte* buffer) {
        return reinterpret_cast<establish_message*>(buffer);
    }

    // parse method const
    static const establish_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const establish_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(establish_message::fields_type, session_id) == 0, "unexpected offset of establish_message::fields_type::session_id");
static_assert(offsetof(establish_message::fields_type, session_ver_id) == 4, "unexpected offset of establish_message::fields_type::session_ver_id");
static_assert(offsetof(establish_message::fields_type, timestamp) == 12, "unexpected offset of establish_message::fields_type::timestamp");
static_assert(offsetof(establish_message::fields_type, keep_alive_interval) == 20, "unexpected offset of establish_message::fields_type::keep_alive_interval");
static_assert(offsetof(establish_message::fields_type, next_seq_no) == 28, "unexpected offset of establish_message::fields_type::next_seq_no");
static_assert(offsetof(establish_message::fields_type, cancel_on_disconnect_type) == 32, "unexpected offset of establish_message::fields_type::cancel_on_disconnect_type");
static_assert(offsetof(establish_message::fields_type, offset_33_padding_1) == 33, "unexpected offset of establish_message::fields_type::offset_33_padding_1");
static_assert(offsetof(establish_message::fields_type, cod_timeout_window) == 34, "unexpected offset of establish_message::fields_type::cod_timeout_window");
static_assert(sizeof(establish_message::fields_type) == 42, "unexpected sizeof establish_message::fields_type");

#pragma pack(pop)
}

#include "details/EstablishMessageWriter.hpp"
#include "details/EstablishMessageReader.hpp"
