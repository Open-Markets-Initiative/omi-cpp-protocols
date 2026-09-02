#pragma once

// Minimal per-flow TCP byte-stream reassembler.
// Tracks one byte stream per (src_ip, src_port, dst_ip, dst_port) and delivers
// in-order bytes via an on_data callback. Out-of-order segments are buffered
// (sorted by sequence) and replayed when the gap fills. Duplicates are dropped.
//
// Scope kept tight on purpose: no SACK, no window/MSS tracking, no half-duplex
// fan-out, no RST handling. Sufficient for replaying a single-side market data
// pcap into a SoupBin/MoldUDP-style consumer. Extend toward Wireshark's tcp.c
// as live-capture quirks demand.

#include "Frame.hpp"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

namespace packet {

struct TcpFlowKey {
    std::uint32_t src_ip   = 0;  // network byte order
    std::uint32_t dst_ip   = 0;  // network byte order
    std::uint16_t src_port = 0;  // host byte order
    std::uint16_t dst_port = 0;  // host byte order

    bool operator==(const TcpFlowKey& other) const noexcept = default;

    struct hash {
        std::size_t operator()(const TcpFlowKey& k) const noexcept {
            std::uint64_t lo = (std::uint64_t(k.src_ip) << 32) | k.dst_ip;
            std::uint64_t hi = (std::uint64_t(k.src_port) << 16) | k.dst_port;
            return std::hash<std::uint64_t>{}(lo ^ (hi * 0x9E3779B97F4A7C15ULL));
        }
    };
};

struct TcpFlow {
    std::uint32_t expected_seq = 0;
    bool initialized = false;
    // out-of-order segments keyed by their starting sequence number
    std::map<std::uint32_t, std::vector<std::byte>> pending;
};

struct TcpReassembler {

    static constexpr std::uint8_t SYN = 0x02;
    static constexpr std::uint8_t FIN = 0x01;
    static constexpr std::uint8_t RST = 0x04;

    // Callback invoked with contiguous bytes for a flow. Bytes are ephemeral —
    // copy them out if you need to retain them past the callback.
    std::function<void(const TcpFlowKey&, const std::byte*, std::size_t)> on_data;

    std::unordered_map<TcpFlowKey, TcpFlow, TcpFlowKey::hash> flows;

    void process(const Frame& f) {
        if (!f.is_tcp() || !f.valid()) return;

        TcpFlowKey key{f.src_ip, f.dst_ip, f.src_port, f.dst_port};
        auto& flow = flows[key];

        if (f.tcp_flags & RST) {
            flows.erase(key);
            return;
        }

        if (f.tcp_flags & SYN) {
            // SYN consumes one sequence number — next data starts at seq+1
            flow.expected_seq = f.tcp_seq + 1;
            flow.initialized = true;
            // A SYN may carry payload (rare); fall through to treat it as data
            if (f.payload_len == 0) return;
        }

        if (!flow.initialized) {
            // First seen segment without SYN — accept as origin
            flow.expected_seq = f.tcp_seq;
            flow.initialized = true;
        }

        if (f.payload_len > 0) {
            deliver(key, flow, f.tcp_seq, f.payload, f.payload_len);
        }

        if (f.tcp_flags & FIN) {
            flows.erase(key);
        }
    }

private:

    void deliver(const TcpFlowKey& key, TcpFlow& flow,
                 std::uint32_t seq, const std::byte* data, std::size_t len) {
        // duplicate or fully-retransmitted segment behind the cursor — drop
        if (seq_lt(seq + static_cast<std::uint32_t>(len), flow.expected_seq) ||
            seq + static_cast<std::uint32_t>(len) == flow.expected_seq) {
            return;
        }

        // partial overlap — trim the prefix that's already delivered
        if (seq_lt(seq, flow.expected_seq)) {
            auto skip = flow.expected_seq - seq;
            if (skip >= len) return;
            data += skip;
            len  -= skip;
            seq  += skip;
        }

        if (seq == flow.expected_seq) {
            on_data(key, data, len);
            flow.expected_seq += static_cast<std::uint32_t>(len);
            drain(key, flow);
            return;
        }

        // Out of order — buffer for later
        auto& buf = flow.pending[seq];
        buf.assign(data, data + len);
    }

    void drain(const TcpFlowKey& key, TcpFlow& flow) {
        while (true) {
            auto it = flow.pending.find(flow.expected_seq);
            if (it == flow.pending.end()) break;
            on_data(key, it->second.data(), it->second.size());
            flow.expected_seq += static_cast<std::uint32_t>(it->second.size());
            flow.pending.erase(it);
        }
    }

    // Wrap-aware comparison: a < b in 32-bit sequence space
    static bool seq_lt(std::uint32_t a, std::uint32_t b) {
        return static_cast<std::int32_t>(a - b) < 0;
    }
};

} // namespace packet