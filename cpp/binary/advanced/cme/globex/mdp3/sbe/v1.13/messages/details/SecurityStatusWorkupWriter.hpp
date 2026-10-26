#pragma once

#include "../SecurityStatusWorkup.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class security_status_workup_group_writer;
class security_status_workup_groups_builder;

class security_status_workup_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    security_status_workup_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(security_status_workup_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    security_status_workup_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_status_workup_groups_builder& order_id(std::uint64_t v) {
        if (pos_ + sizeof(security_status_workup_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_status_workup_groups_entry*>(pos_);
        entry->order_id.set(v);
        return *this;
    }

    security_status_workup_groups_builder& side(sbe_mdp3::side::enum_type v) {
        if (pos_ + sizeof(security_status_workup_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_status_workup_groups_entry*>(pos_);
        entry->side.set(v);
        return *this;
    }

    security_status_workup_groups_builder& aggressor_indicator(sbe_mdp3::aggressor_indicator::enum_type v) {
        if (pos_ + sizeof(security_status_workup_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_status_workup_groups_entry*>(pos_);
        entry->aggressor_indicator.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_groups() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class security_status_workup_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_status_workup_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_status_workup_groups_builder start_groups() {
        return { msg_start_, pos_, end_ };
    }
};


inline security_status_workup_group_writer start_group_write(security_status_workup& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + security_status_workup::tail_capacity };
}
}
