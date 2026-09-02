#pragma once

#ifdef HAS_ZLIB

#include "Decompressor.hpp"

#include <memory>
#include <stdexcept>
#include <vector>
#include <zlib.h>

namespace packet {

// Gzip Decompressor — reads compressed bytes from any Decompressor source
struct GzipDecompressor : Decompressor {
    std::unique_ptr<Decompressor> source_;
    z_stream stream_{};
    std::vector<Bytef> inbuf_;
    bool finished_ = false;

    explicit GzipDecompressor(std::unique_ptr<Decompressor> source,
                               std::size_t inbuf_size = 32768)
        : source_(std::move(source)), inbuf_(inbuf_size) {
        stream_.zalloc = Z_NULL;
        stream_.zfree = Z_NULL;
        stream_.opaque = Z_NULL;
        stream_.avail_in = 0;
        stream_.next_in = Z_NULL;
        if (inflateInit2(&stream_, 15 + 16) != Z_OK)
            throw std::runtime_error("inflateInit2 failed");
    }

    ~GzipDecompressor() override { inflateEnd(&stream_); }

    GzipDecompressor(const GzipDecompressor&) = delete;
    GzipDecompressor& operator=(const GzipDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        stream_.next_out = static_cast<Bytef*>(buf);
        stream_.avail_out = static_cast<uInt>(len);
        while (stream_.avail_out > 0 && !finished_) {
            if (stream_.avail_in == 0) {
                auto n = source_->read(inbuf_.data(), inbuf_.size());
                if (n == 0) break;
                stream_.next_in = inbuf_.data();
                stream_.avail_in = static_cast<uInt>(n);
            }
            int ret = inflate(&stream_, Z_NO_FLUSH);
            if (ret == Z_STREAM_END) { finished_ = true; break; }
            if (ret != Z_OK) throw std::runtime_error("inflate error");
        }
        return len - stream_.avail_out;
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif