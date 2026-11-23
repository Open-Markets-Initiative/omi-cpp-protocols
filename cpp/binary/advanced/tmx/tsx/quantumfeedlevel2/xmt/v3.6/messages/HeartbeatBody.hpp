// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/HeartbeatBody.hpp
#pragma once

#include <cstddef>
#include "../structs/FrameHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BodyHeader.hpp"
#include "../types/AdminId.hpp"
#include "../types/HbInterval.hpp"
#include "../types/SourceId.hpp"
#include "../types/StreamId.hpp"
#include "../types/Sequence0.hpp"
#include "../types/Sequence1.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)
struct heartbeat_body_admin_body_entry {
    xmt_quantumfeedlevel2::source_id source_id;
    xmt_quantumfeedlevel2::stream_id stream_id;
    xmt_quantumfeedlevel2::sequence_0 sequence_0;
    xmt_quantumfeedlevel2::sequence_1 sequence_1;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Heartbeat Body
struct heartbeat_body {

    struct fields_type {
        xmt_quantumfeedlevel2::body_header body_header;
        xmt_quantumfeedlevel2::admin_id admin_id;
        xmt_quantumfeedlevel2::hb_interval hb_interval;
    };

    xmt_quantumfeedlevel2::frame_header header = {start_of_frame(2), protocol_name('X'), {}, std::uint16_t(sizeof(xmt_quantumfeedlevel2::frame_header) + sizeof(fields_type) - 5), {}, {}, {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(xmt_quantumfeedlevel2::frame_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return (sz + 5) == sizeof(xmt_quantumfeedlevel2::frame_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 5) - sizeof(xmt_quantumfeedlevel2::frame_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<heartbeat_body_admin_body_entry> admin_body() const {
        return { tail_begin(), header.num_body.get().value(), tail_end() };
    }


    // parse method
    static heartbeat_body* parse(std::byte* buffer) {
        return reinterpret_cast<heartbeat_body*>(buffer);
    }

    // parse method const
    static const heartbeat_body* parse(const std::byte* buffer) {
        return reinterpret_cast<const heartbeat_body*>(buffer);
    }

};

// layout verification
static_assert(offsetof(heartbeat_body::fields_type, body_header) == 0, "unexpected offset of heartbeat_body::fields_type::body_header");
static_assert(offsetof(heartbeat_body::fields_type, admin_id) == 3, "unexpected offset of heartbeat_body::fields_type::admin_id");
static_assert(offsetof(heartbeat_body::fields_type, hb_interval) == 4, "unexpected offset of heartbeat_body::fields_type::hb_interval");
static_assert(sizeof(heartbeat_body::fields_type) == 6, "unexpected sizeof heartbeat_body::fields_type");

#pragma pack(pop)
}

#include "details/HeartbeatBodyWriter.hpp"
#include "details/HeartbeatBodyReader.hpp"
