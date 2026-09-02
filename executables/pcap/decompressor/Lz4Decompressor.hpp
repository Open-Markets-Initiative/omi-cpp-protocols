#pragma once

#ifdef HAS_LZ4

#include "Decompressor.hpp"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>
#include <lz4frame.h>

namespace packet {

// LZ4 frame Decompressor
struct Lz4Decompressor : Decompressor {
    std::unique_ptr<Decompressor> source_;
    LZ4F_dctx* ctx_ = nullptr;
    std::vector<std::byte> inbuf_;
    std::size_t in_pos_ = 0;
    std::size_t in_size_ = 0;
    bool finished_ = false;

    explicit Lz4Decompressor(std::unique_ptr<Decompressor> source,
                              std::size_t inbuf_size = 32768)
        : source_(std::move(source)), inbuf_(inbuf_size) {
        auto err = LZ4F_createDecompressionContext(&ctx_, LZ4F_VERSION);
        if (LZ4F_isError(err))
            throw std::runtime_error("LZ4F_createDecompressionContext failed");
    }

    ~Lz4Decompressor() override {
        if (ctx_) LZ4F_freeDecompressionContext(ctx_);
    }

    Lz4Decompressor(const Lz4Decompressor&) = delete;
    Lz4Decompressor& operator=(const Lz4Decompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        auto* out = static_cast<std::byte*>(buf);
        std::size_t total_out = 0;
        while (total_out < len && !finished_) {
            if (in_pos_ >= in_size_) {
                in_size_ = source_->read(inbuf_.data(), inbuf_.size());
                in_pos_ = 0;
                if (in_size_ == 0) { finished_ = true; break; }
            }
            std::size_t dst_size = len - total_out;
            std::size_t src_size = in_size_ - in_pos_;
            auto ret = LZ4F_decompress(ctx_, out + total_out, &dst_size,
                                        inbuf_.data() + in_pos_, &src_size, nullptr);
            if (LZ4F_isError(ret))
                throw std::runtime_error("LZ4F_decompress error");
            total_out += dst_size;
            in_pos_ += src_size;
            if (ret == 0) { finished_ = true; break; }
        }
        return total_out;
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif