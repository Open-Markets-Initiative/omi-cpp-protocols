#pragma once

#include "decompressor/Decompressor.hpp"

#include <cstddef>
#include <cstring>
#include <memory>
#include <vector>

namespace packet {

constexpr std::size_t default_buffer_size = 65536;

// Pcap buffer — decompressed byte buffer with refill/shift
class PcapBuffer {
    std::unique_ptr<Decompressor> source_;
    std::vector<std::byte> buf_;
    std::size_t pos_ = 0;
    std::size_t valid_ = 0;

public:
    explicit PcapBuffer(std::unique_ptr<Decompressor> source,
                         std::size_t buf_size = default_buffer_size)
        : source_(std::move(source)), buf_(buf_size) {}

    PcapBuffer(const PcapBuffer&) = delete;
    PcapBuffer& operator=(const PcapBuffer&) = delete;
    PcapBuffer(PcapBuffer&&) = default;
    PcapBuffer& operator=(PcapBuffer&&) = default;

    bool ensure(std::size_t n) {
        if (n > buf_.size()) return false;
        while (available() < n) {
            if (!refill()) return false;
        }
        return true;
    }

    std::size_t available() const { return valid_ - pos_; }
    const std::byte* data() const { return buf_.data() + pos_; }
    void consume(std::size_t n) { pos_ += n; }

private:
    bool refill() {
        std::size_t remaining = valid_ - pos_;
        if (pos_ > 0) {
            if (remaining > 0)
                std::memmove(buf_.data(), buf_.data() + pos_, remaining);
            pos_ = 0;
            valid_ = remaining;
        }
        std::size_t space = buf_.size() - valid_;
        if (space == 0) return false;
        auto got = source_->read(buf_.data() + valid_, space);
        valid_ += got;
        return got > 0;
    }
};

} // namespace packet