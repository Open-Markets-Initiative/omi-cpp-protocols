#pragma once

#include "RawDecompressor.hpp"
#include "PrefixedDecompressor.hpp"
#include "GzipDecompressor.hpp"
#include "Bzip2Decompressor.hpp"
#include "LzmaDecompressor.hpp"
#include "Lz4Decompressor.hpp"
#include "ZstdDecompressor.hpp"

#include <memory>
#include <stdexcept>
#include <string>

namespace packet {

// detect_and_wrap — peek magic bytes from any Decompressor, wrap if compressed.
// Works on any source: raw files, zip entries, or chained Decompressors.
inline std::unique_ptr<Decompressor>
detect_and_wrap(std::unique_ptr<Decompressor> source) {
    unsigned char magic[6]{};
    auto n = source->read(magic, 6);

    // Prepend the peeked bytes back so the next reader sees the full stream
    auto prefixed = std::make_unique<PrefixedDecompressor>(
        std::move(source), magic, n);

#ifdef HAS_ZLIB
    if (n >= 2 && magic[0] == 0x1f && magic[1] == 0x8b)
        return std::make_unique<GzipDecompressor>(std::move(prefixed));
#endif

#ifdef HAS_BZIP2
    if (n >= 2 && magic[0] == 0x42 && magic[1] == 0x5a)
        return std::make_unique<Bzip2Decompressor>(std::move(prefixed));
#endif

#ifdef HAS_LZMA
    if (n >= 6 && magic[0] == 0xfd && magic[1] == 0x37 && magic[2] == 0x7a
               && magic[3] == 0x58 && magic[4] == 0x5a && magic[5] == 0x00)
        return std::make_unique<LzmaDecompressor>(std::move(prefixed));
#endif

#ifdef HAS_LZ4
    if (n >= 4 && magic[0] == 0x04 && magic[1] == 0x22
               && magic[2] == 0x4d && magic[3] == 0x18)
        return std::make_unique<Lz4Decompressor>(std::move(prefixed));
#endif

#ifdef HAS_ZSTD
    if (n >= 4 && magic[0] == 0x28 && magic[1] == 0xb5
               && magic[2] == 0x2f && magic[3] == 0xfd)
        return std::make_unique<ZstdDecompressor>(std::move(prefixed));
#endif

    // Not compressed — return with prefix replayed (pcap header bytes)
    return prefixed;
}

// open_decompressor — open a file path with auto-detected decompression
inline std::unique_ptr<Decompressor> open_decompressor(const std::string& path) {
    FILE* fp = std::fopen(path.c_str(), "rb");
    if (!fp) throw std::runtime_error("cannot open: " + path);
    return detect_and_wrap(std::make_unique<RawDecompressor>(fp));
}

// is_zip_file — peek at file magic bytes to detect zip archive
inline bool is_zip_file(const std::string& path) {
    FILE* fp = std::fopen(path.c_str(), "rb");
    if (!fp) return false;
    unsigned char magic[4]{};
    auto n = std::fread(magic, 1, 4, fp);
    std::fclose(fp);
    return n >= 4 && magic[0] == 0x50 && magic[1] == 0x4b
                  && magic[2] == 0x03 && magic[3] == 0x04;
}

} // namespace packet