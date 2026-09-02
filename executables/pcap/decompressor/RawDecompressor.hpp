#pragma once

#include "Decompressor.hpp"

#include <cstdio>

namespace packet {

// Raw Decompressor — reads directly from FILE*
// This is the only Decompressor that touches FILE*. All others read from
// a Decompressor source, making the whole stack composable.
struct RawDecompressor : Decompressor {
    FILE* file_;
    bool at_eof_ = false;

    explicit RawDecompressor(FILE* fp) : file_(fp) {}

    ~RawDecompressor() override {
        if (file_) std::fclose(file_);
    }

    RawDecompressor(const RawDecompressor&) = delete;
    RawDecompressor& operator=(const RawDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        auto n = std::fread(buf, 1, len, file_);
        if (n == 0) at_eof_ = true;
        return n;
    }

    bool eof() const override { return at_eof_; }
};

} // namespace packet