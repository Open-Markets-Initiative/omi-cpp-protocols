#pragma once

#ifdef HAS_LIBZIP

#include "Decompressor.hpp"

#include <cstddef>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>

#include <zip.h>

namespace packet {

// Reads decompressed bytes from one entry in a libzip-opened archive.
// libzip handles the actual decompression (DEFLATE / store / etc.) and zip64;
// we get the entry's payload bytes here. Inner compression on those payload
// bytes (e.g. a .pcap.zst entry) is handled by detect_and_wrap.
struct ZipEntryDecompressor : Decompressor {
    std::shared_ptr<zip_t> archive_;
    zip_file_t* entry_ = nullptr;
    bool finished_ = false;

    ZipEntryDecompressor(std::shared_ptr<zip_t> archive, zip_uint64_t index)
        : archive_(std::move(archive)) {
        entry_ = zip_fopen_index(archive_.get(), index, 0);
        if (!entry_)
            throw std::runtime_error("zip_fopen_index failed");
    }

    ~ZipEntryDecompressor() override {
        if (entry_) zip_fclose(entry_);
    }

    ZipEntryDecompressor(const ZipEntryDecompressor&) = delete;
    ZipEntryDecompressor& operator=(const ZipEntryDecompressor&) = delete;

    std::size_t read(void* buf, std::size_t len) override {
        if (finished_) return 0;
        auto n = zip_fread(entry_, buf, len);
        if (n < 0) {
            // Pull detailed error info from libzip — both the libzip error code
            // and the underlying system errno are useful when a zip is corrupt
            // or partially uploaded.
            zip_error_t* ze = zip_file_get_error(entry_);
            int zip_err = ze ? zip_error_code_zip(ze) : -1;
            int sys_err = ze ? zip_error_code_system(ze) : 0;
            const char* zstr = ze ? zip_error_strerror(ze) : "(no error info)";
            std::ostringstream oss;
            oss << "zip_fread failed: n=" << n
                << " libzip_err=" << zip_err
                << " sys_errno=" << sys_err
                << " tid=" << std::this_thread::get_id()
                << " msg=\"" << (zstr ? zstr : "") << "\"";
            throw std::runtime_error(oss.str());
        }
        if (n == 0) finished_ = true;
        return static_cast<std::size_t>(n);
    }

    bool eof() const override { return finished_; }
};

} // namespace packet

#endif // HAS_LIBZIP