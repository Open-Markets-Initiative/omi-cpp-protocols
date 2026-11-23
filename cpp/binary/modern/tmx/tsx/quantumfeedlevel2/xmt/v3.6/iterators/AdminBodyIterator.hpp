// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: iterators/AdminBodyIterator.hpp
#pragma once

#include "../definitions.hpp"
#include "../structs/BodyHeader.hpp"
#include "../types/AdminId.hpp"
#include "../types/HbInterval.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {
// AdminBodyIterator
struct AdminBodyIterator {

    const std::byte* current = nullptr;

    const FrameHeader* frame_header = nullptr;

    std::uint8_t num_body = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        frame_header = FrameHeader::parse(current);
        current += sizeof(FrameHeader);

        num_body = frame_header->num_body.get();

        // the first entry lies elsewhere than where FrameHeader ends: step over what is in front of it
        current += sizeof(BodyHeader);
        current += sizeof(AdminId);
        current += sizeof(HbInterval);

        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= num_body) {
            return false;
        }

        entry = current;
        entry_index++;

        return true;
    }

    // advance past processed entry
    void advance(std::size_t bytes) {
        current += bytes;
    }

    // reset iterator
    void reset() {
        current = nullptr;

        frame_header = nullptr;

        num_body = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
