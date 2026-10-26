#pragma once

#include "../SecurityStatusRequest.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

class security_status_request_group_writer;
class security_status_request_security_groups_builder;
class security_status_request_after_security;
class security_status_request_related_symbol_groups_builder;

class security_status_request_security_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    security_status_request_security_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(security_status_request_security_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    security_status_request_security_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_status_request_security_groups_builder& security_group(std::string_view v) {
        if (pos_ + sizeof(security_status_request_security_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_status_request_security_groups_entry*>(pos_);
        entry->security_group.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    security_status_request_after_security end_security();
};

class security_status_request_related_symbol_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    security_status_request_related_symbol_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(security_status_request_related_symbol_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    security_status_request_related_symbol_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_status_request_related_symbol_groups_builder& security_id(std::int32_t v) {
        if (pos_ + sizeof(security_status_request_related_symbol_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_status_request_related_symbol_groups_entry*>(pos_);
        entry->security_id.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_related_symbol() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class security_status_request_after_security {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_status_request_after_security(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_status_request_related_symbol_groups_builder start_related_symbol() {
        return { msg_start_, pos_, end_ };
    }
};

class security_status_request_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_status_request_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_status_request_security_groups_builder start_security() {
        return { msg_start_, pos_, end_ };
    }
};

inline security_status_request_after_security security_status_request_security_groups_builder::end_security() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}



inline security_status_request_group_writer start_group_write(security_status_request& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + security_status_request::tail_capacity };
}
}
