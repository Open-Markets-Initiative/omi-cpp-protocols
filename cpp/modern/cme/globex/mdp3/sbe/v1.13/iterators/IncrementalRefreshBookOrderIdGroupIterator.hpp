#pragma once

#include "../definitions.hpp"

namespace cme::mdp3::v13 {
// IncrementalRefreshBookOrderIdGroupIterator
struct IncrementalRefreshBookOrderIdGroupIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const GroupSize8Byte* group_size_8_byte = nullptr;

    std::uint16_t block_length = 0;
    std::uint8_t num_in_group = 0;
    std::uint8_t entry_index = 0;
    const std::byte* entry = nullptr;
    bool overrun = false;

    // initialize group iterator over the bytes up to the frame's end
    void initialize(const std::byte* data, const std::byte* bound) {

        current = data;
        end = bound;
        entry_index = 0;
        entry = nullptr;
        overrun = false;

        if (current + sizeof(GroupSize8Byte) > end) {
            group_size_8_byte = nullptr;
            block_length = 0;
            num_in_group = 0;
            overrun = true;
            return;
        }

        group_size_8_byte = GroupSize8Byte::parse(current);
        current += sizeof(GroupSize8Byte);

        block_length = group_size_8_byte->block_length.get();
        num_in_group = group_size_8_byte->num_in_group.get();
    }

    // next entry
    bool next() {

        if (entry_index >= num_in_group) {
            return false;
        }

        // a count the frame cannot hold (a corrupt dimension) ends the group at the frame's end
        if (current + block_length > end) {
            overrun = true;
            entry_index = num_in_group;
            return false;
        }

        entry = current;
        entry_index++;
        current += block_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        group_size_8_byte = nullptr;

        block_length = 0;
        num_in_group = 0;
        entry_index = 0;
        entry = nullptr;
        overrun = false;
    }
};
}
