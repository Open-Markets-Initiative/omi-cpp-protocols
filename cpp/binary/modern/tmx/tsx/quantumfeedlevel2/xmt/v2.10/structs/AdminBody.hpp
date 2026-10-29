#pragma once

#include "../types/SourceId.hpp"
#include "../types/StreamId.hpp"
#include "../types/Sequence0.hpp"
#include "../types/Sequence1.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

#pragma pack(push, 1)

struct AdminBody {

    SourceId source_id;
    StreamId stream_id;
    Sequence0 sequence_0;
    Sequence1 sequence_1;

    // parse method
    static AdminBody* parse(std::byte* buffer) {
        return reinterpret_cast<AdminBody*>(buffer);
    }

    // parse method const
    static const AdminBody* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdminBody*>(buffer);
    }
};

#pragma pack(pop)
}
