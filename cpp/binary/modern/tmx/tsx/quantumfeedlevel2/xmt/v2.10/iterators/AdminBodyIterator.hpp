#pragma once

#include "../definitions.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {
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
