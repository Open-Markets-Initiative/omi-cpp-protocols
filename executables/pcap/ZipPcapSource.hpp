#pragma once

#ifdef HAS_LIBZIP

#include "PcapSource.hpp"
#include "PcapFile.hpp"
#include "decompressor/Decompressor.hpp"
#include "decompressor/Detect.hpp"
#include "decompressor/ZipEntryDecompressor.hpp"

#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <zip.h>

namespace packet {

// A zip entry exposed as a PcapSource together with a human-readable display
// path of the form "{archive}!{entry}" used for error reporting.
struct ZipPcapEntry {
    std::unique_ptr<PcapSource> source;
    std::string display_path;
};

// Strip known compression suffixes from `name` to find the base extension,
// then check whether the base ends in .pcap or .cap. Returns true if so —
// these are the entries we want to feed to a PcapFile.
inline bool is_pcap_entry(const std::string& name) {
    auto base = name;

    constexpr const char* suffixes[] = {
        ".zst", ".gz", ".bz2", ".xz", ".lz4", ".lzo", ".Z"
    };
    for (const auto* suffix : suffixes) {
        auto slen = std::strlen(suffix);
        if (base.size() > slen && base.substr(base.size() - slen) == suffix) {
            base = base.substr(0, base.size() - slen);
            break;
        }
    }

    if (base.size() >= 5 && base.substr(base.size() - 5) == ".pcap") return true;
    if (base.size() >= 4 && base.substr(base.size() - 4) == ".cap")  return true;
    return false;
}

// Open every pcap-looking entry in `path` as a PcapFile-backed PcapSource.
// Each entry goes through detect_and_wrap so inner compression (.pcap.zst,
// .pcap.gz, etc.) is handled transparently.
//
// If `entry_filter` is provided, only entries whose bare name passes the
// filter are loaded. Filtered-out entries are not opened, not parsed, and
// do not count as corrupt.
//
// Per-entry failures are caught, logged to stderr, and counted in
// `corrupt_count`. The function only throws if the archive itself can't
// be opened.
inline std::vector<ZipPcapEntry>
open_zip_pcaps(const std::string& path, std::size_t& corrupt_count,
               const std::function<bool(const std::string&)>& entry_filter = {}) {
    int err = 0;
    auto* raw = zip_open(path.c_str(), ZIP_RDONLY, &err);
    if (!raw)
        throw std::runtime_error("zip_open failed: " + path);

    // Shared ownership — archive stays open until all entry decompressors are done
    auto archive = std::shared_ptr<zip_t>(raw, [](zip_t* z) { zip_close(z); });

    auto num_entries = zip_get_num_entries(archive.get(), 0);
    std::vector<ZipPcapEntry> entries;
    std::size_t pcap_entries_seen = 0;
    std::size_t pcap_entries_kept = 0;

    for (zip_int64_t i = 0; i < num_entries; i++) {
        const char* entry_name = zip_get_name(
            archive.get(), static_cast<zip_uint64_t>(i), 0);
        if (!entry_name) continue;
        if (!is_pcap_entry(entry_name)) continue;

        pcap_entries_seen++;

        if (entry_filter && !entry_filter(entry_name)) continue;

        pcap_entries_kept++;

        std::string display = path + "!" + entry_name;

        try {
            auto entry_dec = std::make_unique<ZipEntryDecompressor>(
                archive, static_cast<zip_uint64_t>(i));
            auto final_dec = detect_and_wrap(std::move(entry_dec));
            auto source = std::make_unique<PcapFile>(std::move(final_dec));
            entries.push_back({std::move(source), std::move(display)});
        } catch (const std::exception& e) {
            std::cerr << "WARNING: zip entry [" << display
                      << "] failed to open: " << e.what()
                      << ". skipping.\n";
            corrupt_count++;
        }
    }

    if (entry_filter) {
        std::cerr << "filter: kept " << pcap_entries_kept
                  << " of " << pcap_entries_seen
                  << " pcap entries from " << path << "\n";
    }

    return entries;
}

} // namespace packet

#endif // HAS_LIBZIP