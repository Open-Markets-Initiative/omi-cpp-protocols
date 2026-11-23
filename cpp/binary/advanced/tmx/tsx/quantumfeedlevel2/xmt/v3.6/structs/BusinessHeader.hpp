// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BusinessHeader.hpp
#pragma once

#include <cstddef>
#include "../types/MsgVersion.hpp"
#include "../types/SourceId.hpp"
#include "../types/StreamId.hpp"
#include "../types/Sequence0.hpp"
#include "../types/Sequence1.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

struct business_header {

    xmt_quantumfeedlevel2::msg_version msg_version;
    xmt_quantumfeedlevel2::source_id source_id;
    xmt_quantumfeedlevel2::stream_id stream_id;
    xmt_quantumfeedlevel2::sequence_0 sequence_0;
    xmt_quantumfeedlevel2::sequence_1 sequence_1;

    // parse method
    static business_header* parse(std::byte* buffer) {
        return reinterpret_cast<business_header*>(buffer);
    }

    // parse method const
    static const business_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const business_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(business_header, msg_version) == 0, "unexpected offset of business_header::msg_version");
static_assert(offsetof(business_header, source_id) == 1, "unexpected offset of business_header::source_id");
static_assert(offsetof(business_header, stream_id) == 2, "unexpected offset of business_header::stream_id");
static_assert(offsetof(business_header, sequence_0) == 4, "unexpected offset of business_header::sequence_0");
static_assert(offsetof(business_header, sequence_1) == 5, "unexpected offset of business_header::sequence_1");
static_assert(sizeof(business_header) == 9, "unexpected sizeof business_header");

#pragma pack(pop)
}
