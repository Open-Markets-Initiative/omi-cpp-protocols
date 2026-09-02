#pragma once

#include "PcapSource.hpp"
#include "PcapBuffer.hpp"
#include "decompressor/Detect.hpp"

#include <bit>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

namespace packet {

// Pcap file reader — reads one pcap file, producing packets sequentially
struct PcapFile : PcapSource {

    // Construct from file path (auto-detects compression + pcap format)
    explicit PcapFile(const std::string& path,
                       std::size_t buf_size = default_buffer_size)
        : buffer_(open_decompressor(path), buf_size) {
        parse_file_header();
    }

    // Construct from pre-built Decompressor (zip entries, chained Decompressors)
    explicit PcapFile(std::unique_ptr<Decompressor> dec,
                       std::size_t buf_size = default_buffer_size)
        : buffer_(std::move(dec), buf_size) {
        parse_file_header();
    }

    PcapFile(const PcapFile&) = delete;
    PcapFile& operator=(const PcapFile&) = delete;
    PcapFile(PcapFile&&) = default;
    PcapFile& operator=(PcapFile&&) = default;

    bool advance() override {
        if (done_) return false;
        return is_pcapng_ ? advance_pcapng() : advance_classic();
    }

    std::uint64_t timestamp_ns() const override { return ts_ns_; }
    const std::byte* data() const override { return pkt_data_; }
    std::uint32_t length() const override { return pkt_len_; }
    bool done() const override { return done_; }

private:
    PcapBuffer buffer_;
    bool swap_bytes_ = false;
    bool nanosecond_ts_ = false;
    bool is_pcapng_ = false;
    bool done_ = false;

    // Current packet state
    std::uint64_t ts_ns_ = 0;
    const std::byte* pkt_data_ = nullptr;
    std::uint32_t pkt_len_ = 0;

    // Pcap-ng interface tracking
    struct InterfaceInfo {
        std::uint64_t ts_resol = 1000000;  // default: microsecond (10^6)
    };
    std::vector<InterfaceInfo> interfaces_;

    // --- Endian helpers ---
    std::uint16_t fix16(std::uint16_t v) const { return swap_bytes_ ? std::byteswap(v) : v; }
    std::uint32_t fix32(std::uint32_t v) const { return swap_bytes_ ? std::byteswap(v) : v; }
    std::uint64_t fix64(std::uint64_t v) const { return swap_bytes_ ? std::byteswap(v) : v; }

    // --- Header parsing ---

    void parse_file_header() {
        if (!buffer_.ensure(4))
            throw std::runtime_error("file too short for pcap header");

        std::uint32_t magic;
        std::memcpy(&magic, buffer_.data(), 4);

        if (magic == 0x0a0d0d0a) {
            is_pcapng_ = true;
            parse_pcapng_shb();
        } else {
            parse_classic_header(magic);
        }
    }

    void parse_classic_header(std::uint32_t magic) {
        switch (magic) {
        case 0xa1b2c3d4: swap_bytes_ = false; nanosecond_ts_ = false; break;
        case 0xd4c3b2a1: swap_bytes_ = true;  nanosecond_ts_ = false; break;
        case 0xa1b23c4d: swap_bytes_ = false; nanosecond_ts_ = true;  break;
        case 0x4d3cb2a1: swap_bytes_ = true;  nanosecond_ts_ = true;  break;
        default:
            throw std::runtime_error("invalid pcap magic number");
        }
        if (!buffer_.ensure(24))
            throw std::runtime_error("truncated pcap global header");
        buffer_.consume(24);
    }

    // --- Classic pcap packet iteration ---

    bool advance_classic() {
        if (!buffer_.ensure(16)) { done_ = true; return false; }

        std::uint32_t ts_sec, ts_usec, caplen;
        std::memcpy(&ts_sec,  buffer_.data(),      4);
        std::memcpy(&ts_usec, buffer_.data() + 4,  4);
        std::memcpy(&caplen,  buffer_.data() + 8,  4);
        buffer_.consume(16);

        ts_sec  = fix32(ts_sec);
        ts_usec = fix32(ts_usec);
        caplen  = fix32(caplen);

        if (!buffer_.ensure(caplen)) { done_ = true; return false; }

        pkt_data_ = buffer_.data();
        pkt_len_  = caplen;

        if (nanosecond_ts_) {
            ts_ns_ = static_cast<std::uint64_t>(ts_sec) * 1000000000ULL + ts_usec;
        } else {
            ts_ns_ = static_cast<std::uint64_t>(ts_sec) * 1000000000ULL
                   + static_cast<std::uint64_t>(ts_usec) * 1000ULL;
        }

        buffer_.consume(caplen);
        return true;
    }

    // --- Pcap-ng parsing ---

    void parse_pcapng_shb() {
        if (!buffer_.ensure(12))
            throw std::runtime_error("truncated pcap-ng SHB");

        std::uint32_t bom;
        std::memcpy(&bom, buffer_.data() + 8, 4);

        if (bom == 0x1a2b3c4d) {
            swap_bytes_ = false;
        } else if (bom == 0x4d3c2b1a) {
            swap_bytes_ = true;
        } else {
            throw std::runtime_error("invalid pcap-ng byte order magic");
        }

        std::uint32_t block_len;
        std::memcpy(&block_len, buffer_.data() + 4, 4);
        block_len = fix32(block_len);

        if (!buffer_.ensure(block_len))
            throw std::runtime_error("truncated pcap-ng SHB block");
        buffer_.consume(block_len);
    }

    bool advance_pcapng() {
        while (true) {
            if (!buffer_.ensure(8)) { done_ = true; return false; }

            std::uint32_t block_type, block_len;
            std::memcpy(&block_type, buffer_.data(),     4);
            std::memcpy(&block_len,  buffer_.data() + 4, 4);

            block_type = fix32(block_type);
            block_len  = fix32(block_len);

            if (block_len < 12) { done_ = true; return false; }
            if (!buffer_.ensure(block_len)) { done_ = true; return false; }

            const std::byte* block = buffer_.data();

            switch (block_type) {
            case 0x0a0d0d0a:  // SHB — new section
                parse_pcapng_new_section(block);
                break;

            case 1:  // IDB — Interface Description Block
                parse_pcapng_idb(block, block_len);
                break;

            case 6: {  // EPB — Enhanced Packet Block
                if (parse_pcapng_epb(block, block_len)) {
                    buffer_.consume(block_len);
                    return true;
                }
                break;
            }

            default:
                break;
            }

            buffer_.consume(block_len);
        }
    }

    void parse_pcapng_new_section(const std::byte* block) {
        std::uint32_t bom;
        std::memcpy(&bom, block + 8, 4);
        if (bom == 0x1a2b3c4d) swap_bytes_ = false;
        else if (bom == 0x4d3c2b1a) swap_bytes_ = true;
        interfaces_.clear();
    }

    void parse_pcapng_idb(const std::byte* block, std::uint32_t block_len) {
        InterfaceInfo iface;
        if (block_len > 16 + 4) {
            parse_idb_options(block + 16, block_len - 16 - 4, iface);
        }
        interfaces_.push_back(iface);
    }

    void parse_idb_options(const std::byte* opts, std::uint32_t opts_len,
                           InterfaceInfo& iface) {
        std::size_t pos = 0;
        while (pos + 4 <= opts_len) {
            std::uint16_t opt_code, opt_len;
            std::memcpy(&opt_code, opts + pos,     2);
            std::memcpy(&opt_len,  opts + pos + 2, 2);
            opt_code = fix16(opt_code);
            opt_len  = fix16(opt_len);
            pos += 4;

            if (opt_code == 0) break;
            if (pos + opt_len > opts_len) break;

            if (opt_code == 9 && opt_len == 1) {
                auto val = static_cast<std::uint8_t>(opts[pos]);
                if (val & 0x80) {
                    iface.ts_resol = 1ULL << (val & 0x7f);
                } else {
                    iface.ts_resol = 1;
                    for (std::uint8_t i = 0; i < val; i++)
                        iface.ts_resol *= 10;
                }
            }

            pos += opt_len;
            pos = (pos + 3) & ~std::size_t{3};
        }
    }

    bool parse_pcapng_epb(const std::byte* block, [[maybe_unused]] std::uint32_t block_len) {
        std::uint32_t iface_id, ts_high, ts_low, caplen;
        std::memcpy(&iface_id, block + 8,  4);
        std::memcpy(&ts_high,  block + 12, 4);
        std::memcpy(&ts_low,   block + 16, 4);
        std::memcpy(&caplen,   block + 20, 4);

        iface_id = fix32(iface_id);
        ts_high  = fix32(ts_high);
        ts_low   = fix32(ts_low);
        caplen   = fix32(caplen);

        pkt_data_ = block + 28;
        pkt_len_  = caplen;

        std::uint64_t ts = (static_cast<std::uint64_t>(ts_high) << 32) | ts_low;
        std::uint64_t resol = (iface_id < interfaces_.size())
                            ? interfaces_[iface_id].ts_resol
                            : 1000000ULL;

        if (resol == 1000000000ULL) {
            ts_ns_ = ts;
        } else if (resol == 1000000ULL) {
            ts_ns_ = ts * 1000ULL;
        } else if (resol > 0) {
            ts_ns_ = static_cast<std::uint64_t>(
                static_cast<double>(ts) * 1e9 / static_cast<double>(resol));
        } else {
            ts_ns_ = 0;
        }

        return true;
    }
};

} // namespace packet