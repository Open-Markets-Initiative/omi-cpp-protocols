#pragma once

#include "Decompressor.hpp"

#include <cstring>
#include <memory>

namespace packet {

// Prefixed Decompressor — replays a small prefix then delegates to inner source.
// Used after peeking magic bytes for format detection.
struct PrefixedDecompressor : Decompressor {
    std::unique_ptr<Decompressor> inner_;
    unsigned char prefix_[8];
    std::size_t prefix_len_;
    std::size_t prefix_pos_ = 0;

    PrefixedDecompressor(std::unique_ptr<Decompressor> inner,
                          const void* prefix, std::size_t len)
        : inner_(std::move(inner)), prefix_len_(len) {
        std::memcpy(prefix_, prefix, len);
    }

    PrefixedDecompressor(const PrefixedDecompressor&) = delete;
    PrefixedDecompressor& operator=(const PrefixedDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        auto* out = static_cast<unsigned char*>(buf);
        std::size_t total = 0;
        while (total < len && prefix_pos_ < prefix_len_) {
            out[total++] = prefix_[prefix_pos_++];
        }
        if (total < len) {
            total += inner_->read(out + total, len - total);
        }
        return total;
    }

    bool eof() const override {
        return prefix_pos_ >= prefix_len_ && inner_->eof();
    }
};

} // namespace packet