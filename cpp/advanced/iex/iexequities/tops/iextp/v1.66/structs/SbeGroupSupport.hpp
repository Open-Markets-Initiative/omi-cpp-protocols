#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_66 {

template <typename Entry, typename Header>
class sbe_group_iterator {
    const std::byte* begin_;
    const std::byte* end_;
    const std::byte* current_;
    uint16_t block_length_;
    uint16_t num_in_group_;
    uint16_t index_;

  public:
    sbe_group_iterator(const std::byte* data, const std::byte* buffer_end)
        : begin_(data), end_(buffer_end) {
        if (begin_ + sizeof(Header) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const Header*>(begin_);
        block_length_ = hdr->block_length.get().value();
        num_in_group_ = hdr->num_in_group.get().value();
        current_ = begin_ + sizeof(Header);
        index_ = 0;
    }

    bool has_next() const { return index_ < num_in_group_; }

    const Entry& next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        if (current_ + block_length_ > end_) throw std::runtime_error("buffer overrun reading group entry");
        auto* entry = reinterpret_cast<const Entry*>(current_);
        current_ += block_length_;
        ++index_;
        return *entry;
    }

    const std::byte* finalize() {
        const std::byte* past = begin_ + sizeof(Header) + (static_cast<std::size_t>(block_length_) * num_in_group_);
        if (past > end_) throw std::runtime_error("buffer overrun finalizing group");
        return past;
    }
};

class sbe_var_data {
    const std::byte* begin_;
    const std::byte* end_;

  public:
    sbe_var_data(const std::byte* data, const std::byte* buffer_end)
        : begin_(data), end_(buffer_end) {
        if (begin_ + sizeof(uint32_t) > end_) throw std::runtime_error("buffer overrun reading var-data length");
    }

    uint32_t length() const { return *reinterpret_cast<const uint32_t*>(begin_); }
    const char* data() const { return reinterpret_cast<const char*>(begin_ + sizeof(uint32_t)); }

    std::string_view view() const {
        if (begin_ + sizeof(uint32_t) + length() > end_) throw std::runtime_error("buffer overrun reading var-data content");
        return { data(), length() };
    }

    const std::byte* finalize() const {
        auto* past = begin_ + sizeof(uint32_t) + length();
        if (past > end_) throw std::runtime_error("buffer overrun finalizing var-data");
        return past;
    }
};

class external_var_data {
    const std::byte* begin_;
    std::size_t length_;

  public:
    external_var_data(const std::byte* data, std::size_t length, const std::byte* buffer_end)
        : begin_(data), length_(length) {
        if (begin_ + length_ > buffer_end) throw std::runtime_error("buffer overrun reading external-length var-data");
    }

    std::size_t length() const { return length_; }
    const char* data() const { return reinterpret_cast<const char*>(begin_); }

    std::string_view view() const { return { data(), length_ }; }

    const std::byte* finalize() const { return begin_ + length_; }
};

template <typename Entry>
class external_count_iterator {
    const std::byte* current_;
    std::uint64_t remaining_;

  public:
    external_count_iterator(const std::byte* data, std::uint64_t count, const std::byte* buffer_end)
        : current_(data), remaining_(count) {
        if (data + count * sizeof(Entry) > buffer_end)
            throw std::runtime_error("buffer overrun reading external-count group");
    }

    bool has_next() const { return remaining_ > 0; }

    const Entry& next() {
        if (remaining_ == 0) throw std::runtime_error("no more entries in external-count group");
        auto* entry = reinterpret_cast<const Entry*>(current_);
        current_ += sizeof(Entry);
        --remaining_;
        return *entry;
    }

    const std::byte* finalize() const { return current_ + remaining_ * sizeof(Entry); }
};
}
