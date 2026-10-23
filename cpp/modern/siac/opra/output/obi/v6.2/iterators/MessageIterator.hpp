#pragma once

#include "../definitions.hpp"

namespace siac::opra::output::obi::v6_2 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;

    const BlockHeader* block_header = nullptr;

    std::uint8_t messages_in_block = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;

    // initialize iterator
    void initialize(const std::byte* data) {

        current = data;

        block_header = BlockHeader::parse(current);
        current += sizeof(BlockHeader);

        messages_in_block = block_header->messages_in_block.get();
        entry_index = 0;
        entry = nullptr;
    }

    // next entry
    bool next() {

        if (entry_index >= messages_in_block) {
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

        block_header = nullptr;

        messages_in_block = 0;
        entry_index = 0;
        entry = nullptr;
    }
};
}
