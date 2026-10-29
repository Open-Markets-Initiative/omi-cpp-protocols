#pragma once

#include "../QuoteRequestRejectMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

class quote_request_reject_message_group_writer;
class quote_request_reject_message_sides_groups_builder;
class quote_request_reject_message_after_sides;
class quote_request_reject_message_after_desk_id;
class quote_request_reject_message_after_memo;

class quote_request_reject_message_sides_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryentrypoint::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    quote_request_reject_message_sides_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryentrypoint::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryentrypoint::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(quote_request_reject_message_sides_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryentrypoint::group_size_encoding);
    }

    quote_request_reject_message_sides_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryentrypoint::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    quote_request_reject_message_sides_groups_builder& side(sbe_binaryentrypoint::side::enum_type v) {
        if (pos_ + sizeof(quote_request_reject_message_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_reject_message_sides_groups_entry*>(pos_);
        entry->side.set(v);
        return *this;
    }

    quote_request_reject_message_sides_groups_builder& account(typename sbe_binaryentrypoint::account::result_type v) {
        if (pos_ + sizeof(quote_request_reject_message_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_reject_message_sides_groups_entry*>(pos_);
        entry->account.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    quote_request_reject_message_after_sides end_sides();
};

class quote_request_reject_message_after_sides {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_request_reject_message_after_sides(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_request_reject_message_after_desk_id desk_id(std::string_view v);
};

class quote_request_reject_message_after_desk_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_request_reject_message_after_desk_id(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_request_reject_message_after_memo memo(std::string_view v);
};

class quote_request_reject_message_after_memo {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_request_reject_message_after_memo(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> text_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_binaryentrypoint::simple_open_framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class quote_request_reject_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_request_reject_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_request_reject_message_sides_groups_builder start_sides() {
        return { msg_start_, pos_, end_ };
    }
};

inline quote_request_reject_message_after_sides quote_request_reject_message_sides_groups_builder::end_sides() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline quote_request_reject_message_after_desk_id quote_request_reject_message_after_sides::desk_id(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline quote_request_reject_message_after_memo quote_request_reject_message_after_desk_id::memo(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}



inline quote_request_reject_message_group_writer start_group_write(quote_request_reject_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + quote_request_reject_message::tail_capacity };
}
}
