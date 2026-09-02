#pragma once

#ifdef HAS_ZSTD

#include "Decompressor.hpp"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>
#include <zstd.h>

namespace packet {

// Zstd Decompressor
struct ZstdDecompressor : Decompressor {
    std::unique_ptr<Decompressor> source_;
    ZSTD_DStream* dstream_ = nullptr;
    std::vector<std::byte> inbuf_;
    ZSTD_inBuffer input_{};
    bool finished_ = false;

    explicit ZstdDecompressor(std::unique_ptr<Decompressor> source,
                               std::size_t inbuf_size = 32768)
        : source_(std::move(source)), inbuf_(inbuf_size) {
        dstream_ = ZSTD_createDStream();
        if (!dstream_)
            throw std::runtime_error("ZSTD_createDStream failed");
        ZSTD_initDStream(dstream_);
    }

    ~ZstdDecompressor() override {
        if (dstream_) ZSTD_freeDStream(dstream_);
    }

    ZstdDecompressor(const ZstdDecompressor&) = delete;
    ZstdDecompressor& operator=(const ZstdDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        ZSTD_outBuffer output{buf, len, 0};
        while (output.pos < output.size && !finished_) {
            if (input_.pos >= input_.size) {
                auto n = source_->read(inbuf_.data(), inbuf_.size());
                if (n == 0) { finished_ = true; break; }
                input_ = {inbuf_.data(), n, 0};
            }
            auto ret = ZSTD_decompressStream(dstream_, &output, &input_);
            if (ZSTD_isError(ret))
                throw std::runtime_error("ZSTD_decompressStream error");
            if (ret == 0) { finished_ = true; break; }
        }
        return output.pos;
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif