#pragma once

#include "PcapSource.hpp"
#include "PcapFile.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <glob.h>

#ifdef HAS_LIBZIP
#include "ZipPcapSource.hpp"
#endif

namespace packet {

struct PcapIterator : PcapSource {

    struct SourceEntry {
        std::unique_ptr<PcapSource> source;
        std::int64_t offset_ns;
        std::string path;
        bool dead = false;
    };

    // Construct from glob patterns with per-pattern nanosecond offsets
    explicit PcapIterator(std::vector<std::pair<std::string, std::int64_t>> specs) {
        for (auto& [pattern, offset] : specs) {
            expand_glob(pattern, offset);
        }
        init_queue();
    }

    // Construct from glob patterns with a per-zip-entry filter. The filter
    // receives bare entry names (e.g. "ny4-opra-pillar-3-b-...pcap.zst") and
    // returns true to keep the entry. Entries skipped by the filter are not
    // opened or parsed. Plain (non-zip) sources ignore the filter.
    explicit PcapIterator(std::vector<std::pair<std::string, std::int64_t>> specs,
                          std::function<bool(const std::string&)> entry_filter)
        : entry_filter_(std::move(entry_filter)) {
        for (auto& [pattern, offset] : specs) {
            expand_glob(pattern, offset);
        }
        init_queue();
    }

    // Construct from pre-built sources (used internally)
    explicit PcapIterator(std::vector<SourceEntry> entries)
        : sources_(std::move(entries)) {
        init_queue();
    }

    PcapIterator(const PcapIterator&) = delete;
    PcapIterator& operator=(const PcapIterator&) = delete;
    PcapIterator(PcapIterator&&) = default;
    PcapIterator& operator=(PcapIterator&&) = default;

    bool advance() override {
        if (done_) return false;

        // Lazy advance: push the previous current source back into the queue.
        // If it throws mid-stream (e.g. corrupt zstd), drop it and continue
        // with the next source.
        if (has_current_) {
            try {
                auto& entry = sources_[current_];
                if (entry.source->advance()) {
                    queue_.push({adjusted_time(current_), current_});
                }
            } catch (const std::exception& e) {
                std::cerr << "WARNING: source [" << sources_[current_].path
                          << "] failed mid-stream: " << e.what()
                          << ". dropping.\n";
                sources_[current_].dead = true;
                corrupt_sources_++;
                // Fall through — pick next source from queue
            }
        }

        if (queue_.empty()) {
            done_ = true;
            return false;
        }

        auto top = queue_.top();
        queue_.pop();
        current_ = top.source_index;
        has_current_ = true;

        return true;
    }

    // Adjusted timestamp (raw + offset)
    std::uint64_t timestamp_ns() const override {
        auto raw = sources_[current_].source->timestamp_ns();
        return static_cast<std::uint64_t>(
            static_cast<std::int64_t>(raw) + sources_[current_].offset_ns);
    }

    // Original timestamp from pcap (before offset adjustment)
    std::uint64_t raw_time() const {
        return sources_[current_].source->timestamp_ns();
    }

    const std::byte* data() const override {
        return sources_[current_].source->data();
    }

    std::uint32_t length() const override {
        return sources_[current_].source->length();
    }

    bool done() const override { return done_; }

    std::size_t source_count() const { return sources_.size(); }
    std::size_t corrupt_source_count() const { return corrupt_sources_; }

private:
    struct queue_entry {
        std::uint64_t adjusted_time;
        std::size_t source_index;
        bool operator>(const queue_entry& other) const {
            return adjusted_time > other.adjusted_time;
        }
    };

    std::vector<SourceEntry> sources_;
    std::priority_queue<queue_entry, std::vector<queue_entry>, std::greater<queue_entry>> queue_;
    std::size_t current_ = 0;
    bool has_current_ = false;
    bool done_ = false;
    std::size_t corrupt_sources_ = 0;
    std::function<bool(const std::string&)> entry_filter_;

    std::uint64_t adjusted_time(std::size_t idx) const {
        auto raw = sources_[idx].source->timestamp_ns();
        return static_cast<std::uint64_t>(
            static_cast<std::int64_t>(raw) + sources_[idx].offset_ns);
    }

    void init_queue() {
        // Advance each source once. If a source throws on its first advance
        // (corrupt file, bad header, etc.), drop it from the queue and
        // continue with the survivors.
        for (std::size_t i = 0; i < sources_.size(); i++) {
            try {
                if (sources_[i].source->advance()) {
                    queue_.push({adjusted_time(i), i});
                }
            } catch (const std::exception& e) {
                std::cerr << "WARNING: source [" << sources_[i].path
                          << "] failed on first advance: " << e.what()
                          << ". skipping.\n";
                sources_[i].dead = true;
                corrupt_sources_++;
            }
        }
        done_ = queue_.empty();
    }

    void expand_glob(const std::string& pattern, std::int64_t offset) {
        glob_t g{};
        int ret = ::glob(pattern.c_str(), GLOB_TILDE | GLOB_NOCHECK, nullptr, &g);
        if (ret != 0 && ret != GLOB_NOMATCH) {
            globfree(&g);
            throw std::runtime_error("glob failed for: " + pattern);
        }

        for (std::size_t i = 0; i < g.gl_pathc; i++) {
            std::string path = g.gl_pathv[i];
            add_source(path, offset);
        }
        globfree(&g);
    }

    void add_source(const std::string& path, std::int64_t offset) {
        if (has_zip_extension(path)) {
#ifdef HAS_LIBZIP
            auto zip_entries = open_zip_pcaps(path, corrupt_sources_, entry_filter_);
            for (auto& e : zip_entries) {
                sources_.push_back({std::move(e.source), offset, std::move(e.display_path), false});
            }
#else
            throw std::runtime_error("zip file detected but HAS_LIBZIP not compiled: " + path);
#endif
        } else {
            try {
                sources_.push_back({std::make_unique<PcapFile>(path), offset, path, false});
            } catch (const std::exception& e) {
                std::cerr << "WARNING: source [" << path
                          << "] failed to open: " << e.what()
                          << ". skipping.\n";
                corrupt_sources_++;
            }
        }
    }

    static bool has_zip_extension(const std::string& path) {
        if (path.size() < 4) return false;
        auto ext = path.substr(path.size() - 4);
        return ext == ".zip" || ext == ".ZIP";
    }
};

} // namespace packet