#pragma once

#include "../types/MsgVersion.hpp"
#include "../types/SourceId.hpp"
#include "../types/StreamId.hpp"
#include "../types/Sequence0.hpp"
#include "../types/Sequence1.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

struct BusinessHeader {

    MsgVersion msg_version;
    SourceId source_id;
    StreamId stream_id;
    Sequence0 sequence_0;
    Sequence1 sequence_1;

    // parse method
    static BusinessHeader* parse(std::byte* buffer) {
        return reinterpret_cast<BusinessHeader*>(buffer);
    }

    // parse method const
    static const BusinessHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const BusinessHeader*>(buffer);
    }
};

#pragma pack(pop)
}
