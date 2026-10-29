#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/RefMsgType.hpp"
#include "../types/Offset19Padding1.hpp"
#include "../types/RefSeqNum.hpp"
#include "../types/BusinessRejectRefId.hpp"
#include "../types/BusinessRejectReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// Business Message Reject Message
struct business_message_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::ref_msg_type ref_msg_type;
        sbe_binaryentrypoint::offset_19_padding_1 offset_19_padding_1;
        sbe_binaryentrypoint::ref_seq_num ref_seq_num;
        sbe_binaryentrypoint::business_reject_ref_id business_reject_ref_id;
        sbe_binaryentrypoint::business_reject_reason business_reject_reason;
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
    sbe_var_data memo() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data text(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static business_message_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<business_message_reject_message*>(buffer);
    }

    // parse method const
    static const business_message_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const business_message_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(business_message_reject_message::fields_type, outbound_business_header) == 0, "unexpected offset of business_message_reject_message::fields_type::outbound_business_header");
static_assert(offsetof(business_message_reject_message::fields_type, ref_msg_type) == 18, "unexpected offset of business_message_reject_message::fields_type::ref_msg_type");
static_assert(offsetof(business_message_reject_message::fields_type, offset_19_padding_1) == 19, "unexpected offset of business_message_reject_message::fields_type::offset_19_padding_1");
static_assert(offsetof(business_message_reject_message::fields_type, ref_seq_num) == 20, "unexpected offset of business_message_reject_message::fields_type::ref_seq_num");
static_assert(offsetof(business_message_reject_message::fields_type, business_reject_ref_id) == 24, "unexpected offset of business_message_reject_message::fields_type::business_reject_ref_id");
static_assert(offsetof(business_message_reject_message::fields_type, business_reject_reason) == 32, "unexpected offset of business_message_reject_message::fields_type::business_reject_reason");
static_assert(sizeof(business_message_reject_message::fields_type) == 36, "unexpected sizeof business_message_reject_message::fields_type");

#pragma pack(pop)
}

#include "details/BusinessMessageRejectMessageWriter.hpp"
#include "details/BusinessMessageRejectMessageReader.hpp"
