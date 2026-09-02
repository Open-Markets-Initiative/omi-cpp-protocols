#pragma once

// Zero-copy ethernet frame dissector
// Parses: Ethernet II -> optional 802.1Q VLAN -> IPv4 -> UDP/TCP
// All pointers reference the original buffer — no copies
// Self-contained byte-order helpers via memcpy + shift-or

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace packet {

struct Frame {

    // --- Public fields (pre-extracted, host byte order unless noted) ---

    const std::byte* payload = nullptr;  // L4 payload start (nullptr if invalid)
    std::uint32_t payload_len = 0;       // Payload bytes
    std::uint16_t src_port = 0;          // Host byte order
    std::uint16_t dst_port = 0;          // Host byte order
    std::uint8_t  ip_protocol = 0;       // 6=TCP, 17=UDP
    std::uint16_t vlan_id = 0;           // 0 if no VLAN, else 12-bit VID
    std::uint32_t src_ip = 0;            // Network byte order
    std::uint32_t dst_ip = 0;            // Network byte order
    std::uint32_t tcp_seq = 0;           // Host byte order, TCP only (0 otherwise)
    std::uint8_t  tcp_flags = 0;         // TCP flags byte (SYN=0x02, FIN=0x01, ...), TCP only

    // --- Convenience accessors ---

    bool valid() const { return payload != nullptr; }
    bool is_udp() const { return ip_protocol == 17; }
    bool is_tcp() const { return ip_protocol == 6; }

    std::uint32_t src_ip_host() const { return swap32(src_ip); }
    std::uint32_t dst_ip_host() const { return swap32(dst_ip); }

    // Verify UDP checksum (RFC 768). Returns true for non-UDP frames, invalid
    // frames, and packets with checksum=0 (not computed). Returns true if the
    // computed 1's-complement sum matches the carried checksum, false otherwise.
    bool verify_udp_checksum() const {
        if (!valid() || !is_udp()) return true;

        // UDP header sits 8 bytes before payload
        auto udp_check = read_u16(payload - 8 + 6);
        if (udp_check == 0) return true;  // RFC 768: zero means not computed

        // UDP length from the UDP header (host order via read_u16 byteswap)
        auto udp_len = static_cast<std::uint32_t>(read_u16(payload - 8 + 4));

        // Clamp to what we actually captured
        auto available = len_ - l4_start_;
        if (udp_len > available) udp_len = available;

        // One's complement sum: pseudo-header + UDP segment
        std::uint32_t sum = 0;

        // IPv4 pseudo-header: src_ip(4) + dst_ip(4) + zero(1) + protocol=17(1) + udp_length(2)
        // Read directly from the IP header bytes to keep network-order semantics consistent.
        sum += read_u16(data_ + ip_start_ + 12);
        sum += read_u16(data_ + ip_start_ + 14);
        sum += read_u16(data_ + ip_start_ + 16);
        sum += read_u16(data_ + ip_start_ + 18);
        sum += 17;
        sum += read_u16(data_ + l4_start_ + 4);

        // Sum the entire UDP segment (header + payload) as 16-bit words
        auto* p = data_ + l4_start_;
        std::uint32_t i = 0;
        for (; i + 1 < udp_len; i += 2)
            sum += read_u16(p + i);
        if (i < udp_len)  // odd byte: pad with zero
            sum += static_cast<std::uint32_t>(p[i]) << 8;

        // Fold 32-bit sum into 16 bits
        while (sum >> 16)
            sum = (sum & 0xFFFF) + (sum >> 16);

        return static_cast<std::uint16_t>(sum) == 0xFFFF;
    }

    struct IpOctets {
        std::uint8_t a, b, c, d;
    };

    static IpOctets octets(std::uint32_t ip_net_order) {
        IpOctets o;
        std::memcpy(&o, &ip_net_order, 4);
        return o;
    }

    // --- Constructor: parse frame from raw ethernet data ---

    Frame() = default;

    Frame(const std::byte* data, std::uint32_t len)
        : data_(data), len_(len) {
        parse();
    }

    // --- Original frame access ---

    const std::byte* raw_data() const { return data_; }
    std::uint32_t raw_length() const { return len_; }

private:
    const std::byte* data_ = nullptr;
    std::uint32_t len_ = 0;
    std::uint32_t ip_start_ = 0;   // byte offset of IPv4 header in data_ (0 if invalid)
    std::uint32_t l4_start_ = 0;   // byte offset of L4 header in data_ (0 if invalid)

    // --- Self-contained byte-order helpers ---

    static std::uint16_t read_u16(const std::byte* p) {
        std::uint16_t val;
        std::memcpy(&val, p, sizeof(val));
        return std::byteswap(val);
    }

    static std::uint32_t read_u32(const std::byte* p) {
        return (static_cast<std::uint32_t>(p[0]) << 24)
             | (static_cast<std::uint32_t>(p[1]) << 16)
             | (static_cast<std::uint32_t>(p[2]) << 8)
             |  static_cast<std::uint32_t>(p[3]);
    }

    static std::uint32_t swap32(std::uint32_t v) {
        return ((v >> 24) & 0xFF)
             | ((v >>  8) & 0xFF00)
             | ((v <<  8) & 0xFF0000)
             | ((v << 24) & 0xFF000000u);
    }

    // --- Parse logic ---

    void parse() {
        // Minimum ethernet frame: 14 bytes (6 dst + 6 src + 2 ethertype)
        if (!data_ || len_ < 14) return;

        std::uint32_t offset = 12;
        auto ethertype = read_u16(data_ + offset);
        offset += 2;

        // Linux SLL (cooked capture, 16-byte link header) detection: addr_len at
        // offset 4-5 is typically 6 for ARPHRD_ETHER, ethertype is at offset 14.
        if (ethertype != 0x0800 && ethertype != 0x86DD && ethertype != 0x8100 && ethertype != 0x0806) {
            if (len_ >= 16 && read_u16(data_ + 4) == 6) {
                ethertype = read_u16(data_ + 14);
                offset = 16;
            }
        }

        // 802.1Q VLAN tag
        if (ethertype == 0x8100) {
            if (len_ < offset + 4) return;
            auto tci = read_u16(data_ + offset);
            vlan_id = tci & 0x0FFF;
            ethertype = read_u16(data_ + offset + 2);
            offset += 4;
        }

        // Only IPv4
        if (ethertype != 0x0800) return;

        // IPv4 header: minimum 20 bytes
        auto ip_start = offset;
        ip_start_ = ip_start;
        if (len_ < ip_start + 20) return;

        auto ihl_byte = static_cast<std::uint8_t>(data_[ip_start]);
        auto ip_version = (ihl_byte >> 4) & 0x0F;
        if (ip_version != 4) return;

        auto ip_hdr_len = static_cast<std::uint32_t>(ihl_byte & 0x0F) * 4;
        if (ip_hdr_len < 20) return;
        if (len_ < ip_start + ip_hdr_len) return;

        auto ip_total_len = static_cast<std::uint32_t>(read_u16(data_ + ip_start + 2));

        // Clamp to capture length (truncated captures stay valid)
        auto available = len_ - ip_start;
        if (ip_total_len > available) ip_total_len = available;

        ip_protocol = static_cast<std::uint8_t>(data_[ip_start + 9]);

        // src_ip and dst_ip in network byte order (raw memcpy)
        std::memcpy(&src_ip, data_ + ip_start + 12, 4);
        std::memcpy(&dst_ip, data_ + ip_start + 16, 4);

        auto l4_start = ip_start + ip_hdr_len;
        l4_start_ = l4_start;

        if (ip_protocol == 17) {
            // UDP: 8-byte header
            if (ip_total_len < ip_hdr_len + 8) return;
            if (len_ < l4_start + 8) return;

            src_port = read_u16(data_ + l4_start);
            dst_port = read_u16(data_ + l4_start + 2);

            auto udp_len = static_cast<std::uint32_t>(read_u16(data_ + l4_start + 4));

            // Clamp UDP length to IP total length
            auto max_udp = ip_total_len - ip_hdr_len;
            if (udp_len > max_udp) udp_len = max_udp;

            payload = data_ + l4_start + 8;
            payload_len = (udp_len >= 8) ? (udp_len - 8) : 0;

        } else if (ip_protocol == 6) {
            // TCP: variable header (minimum 20 bytes)
            if (ip_total_len < ip_hdr_len + 20) return;
            if (len_ < l4_start + 20) return;

            src_port = read_u16(data_ + l4_start);
            dst_port = read_u16(data_ + l4_start + 2);
            tcp_seq = read_u32(data_ + l4_start + 4);
            tcp_flags = static_cast<std::uint8_t>(data_[l4_start + 13]);

            auto data_offset_byte = static_cast<std::uint8_t>(data_[l4_start + 12]);
            auto tcp_hdr_len = static_cast<std::uint32_t>((data_offset_byte >> 4) & 0x0F) * 4;
            if (tcp_hdr_len < 20) return;
            if (len_ < l4_start + tcp_hdr_len) return;

            payload = data_ + l4_start + tcp_hdr_len;
            auto ip_payload = ip_total_len - ip_hdr_len;
            payload_len = (ip_payload > tcp_hdr_len) ? (ip_payload - tcp_hdr_len) : 0;
        }
        // Other protocols: payload stays nullptr
    }
};

} // namespace packet