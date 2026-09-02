#pragma once

#ifdef HAS_BZIP2

#include "Decompressor.hpp"

#include <memory>
#include <stdexcept>
#include <vector>
#include <bzlib.h>

namespace packet {

// Bzip2 Decompressor
struct Bzip2Decompressor : Decompressor {
    std::unique_ptr<Decompressor> source_;
    bz_stream stream_{};
    std::vector<char> inbuf_;
    bool finished_ = false;

    explicit Bzip2Decompressor(std::unique_ptr<Decompressor> source,
                                std::size_t inbuf_size = 32768)
        : source_(std::move(source)), inbuf_(inbuf_size) {
        stream_.bzalloc = nullptr;
        stream_.bzfree = nullptr;
        stream_.opaque = nullptr;
        if (BZ2_bzDecompressInit(&stream_, 0, 0) != BZ_OK)
            throw std::runtime_error("BZ2_bzDecompressInit failed");
    }

    ~Bzip2Decompressor() override { BZ2_bzDecompressEnd(&stream_); }

    Bzip2Decompressor(const Bzip2Decompressor&) = delete;
    Bzip2Decompressor& operator=(const Bzip2Decompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        stream_.next_out = static_cast<char*>(buf);
        stream_.avail_out = static_cast<unsigned int>(len);
        while (stream_.avail_out > 0 && !finished_) {
            if (stream_.avail_in == 0) {
                auto n = source_->read(inbuf_.data(), inbuf_.size());
                if (n == 0) break;
                stream_.next_in = inbuf_.data();
                stream_.avail_in = static_cast<unsigned int>(n);
            }
            int ret = BZ2_bzDecompress(&stream_);
            if (ret == BZ_STREAM_END) { finished_ = true; break; }
            if (ret != BZ_OK) throw std::runtime_error("BZ2_bzDecompress error");
        }
        return len - stream_.avail_out;
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif