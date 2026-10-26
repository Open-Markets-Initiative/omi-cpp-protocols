#pragma once

#include "SecurityStatusWorkupWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class security_status_workup_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    security_status_workup_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const security_status_workup_groups_entry& entry() const {
        return *reinterpret_cast<const security_status_workup_groups_entry*>(pos_);
    }

    std::uint64_t order_id() const {
        auto* entry = reinterpret_cast<const security_status_workup_groups_entry*>(pos_);
        return entry->order_id.get().value();
    }

    sbe_mdp3::side::enum_type side() const {
        auto* entry = reinterpret_cast<const security_status_workup_groups_entry*>(pos_);
        return entry->side.get().value();
    }

    sbe_mdp3::aggressor_indicator::enum_type aggressor_indicator() const {
        auto* entry = reinterpret_cast<const security_status_workup_groups_entry*>(pos_);
        return entry->aggressor_indicator.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class security_status_workup_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    security_status_workup_groups_reader(const std::byte* data, const std::byte* end)
        : end_(end) {
        if (data + sizeof(sbe_mdp3::group_size) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const sbe_mdp3::group_size*>(data);
        block_length_ = hdr->block_length.get().value();
        count_ = hdr->num_in_group.get().value();
        pos_ = data + sizeof(sbe_mdp3::group_size);
        index_ = 0;
    }

    uint16_t count() const { return count_; }

    bool has_next() const { return index_ < count_; }

    security_status_workup_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        security_status_workup_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline security_status_workup_groups_reader read_groups(const security_status_workup& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
