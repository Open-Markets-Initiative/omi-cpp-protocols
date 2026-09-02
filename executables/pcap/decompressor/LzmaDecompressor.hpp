#pragma once

#ifdef HAS_LZMA

#include "Decompressor.hpp"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>
#include <lzma.h>

namespace packet {

// LZMA/XZ Decompressor
struct LzmaDecompressor : Decompressor {
    std::unique_ptr<Decompressor> source_;
    lzma_stream stream_;
    std::vector<std::uint8_t> inbuf_;
    bool finished_ = false;

    explicit LzmaDecompressor(std::unique_ptr<Decompressor> source,
                               std::size_t inbuf_size = 32768)
        : source_(std::move(source)), stream_(LZMA_STREAM_INIT), inbuf_(inbuf_size) {
        if (lzma_stream_decoder(&stream_, UINT64_MAX, 0) != LZMA_OK)
            throw std::runtime_error("lzma_stream_decoder failed");
    }

    ~LzmaDecompressor() override { lzma_end(&stream_); }

    LzmaDecompressor(const LzmaDecompressor&) = delete;
    LzmaDecompressor& operator=(const LzmaDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        stream_.next_out = static_cast<std::uint8_t*>(buf);
        stream_.avail_out = len;
        while (stream_.avail_out > 0 && !finished_) {
            if (stream_.avail_in == 0) {
                auto n = source_->read(inbuf_.data(), inbuf_.size());
                if (n == 0) {
                    auto ret = lzma_code(&stream_, LZMA_FINISH);
                    if (ret == LZMA_STREAM_END) finished_ = true;
                    break;
                }
                stream_.next_in = inbuf_.data();
                stream_.avail_in = n;
            }
            auto ret = lzma_code(&stream_, LZMA_RUN);
            if (ret == LZMA_STREAM_END) { finished_ = true; break; }
            if (ret != LZMA_OK) throw std::runtime_error("lzma_code error");
        }
        return len - stream_.avail_out;
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif