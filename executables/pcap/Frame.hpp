// Asx.AsxDerivatives.Ntp.Itch.v1.05: pcap/Frame.hpp
#pragma once

// Zero-copy frame dissector over the readers generated from the Ofi stack models: an Ethernet II
// frame with its 802.1ad and 802.1Q tags (Osi.Network.Ethernet.Ip.v2), or a Linux cooked capture
// (Osi.Network.Sll.Ip.v1), then IPv4, then UDP or TCP. All pointers reference the original buffer.
//
// What stays here is what a frame is to its consumers: which link a frame without its link type is
// (a cooked header is told by its address length, as before), tags stacked beyond those the models
// read (the Ethernet model's S-Tag and C-Tag, the cooked model's one C-Tag) stepped over to the
// innermost, IPv4 only, and each field kept as far as the frame is whole enough to give it.

#include "readers/Osi.Network.Ethernet.Ip.v2/EthernetFrameReader.hpp"
#include "readers/Osi.Network.Sll.Ip.v1/SllFrameReader.hpp"

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
    std::uint16_t vlan_id = 0;           // 0 if no VLAN, else the innermost tag's 12-bit VID
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

    // --- Constructor: parse frame from raw link data ---

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

    using EthernetReader = osi::network::ethernet::ip::v2::EthernetFrameReader;
    using SllReader = osi::network::sll::ip::v1::SllFrameReader;

    // the readers hold where each part of the frame last read lies, and are read again for each frame
    static EthernetReader& ethernet() {
        static thread_local EthernetReader reader;
        return reader;
    }

    static SllReader& sll() {
        static thread_local SllReader reader;
        return reader;
    }

    // --- Self-contained byte-order helpers ---

    static std::uint16_t read_u16(const std::byte* p) {
        std::uint16_t val;
        std::memcpy(&val, p, sizeof(val));
        return std::byteswap(val);
    }

    static std::uint32_t swap32(std::uint32_t v) {
        return ((v >> 24) & 0xFF)
             | ((v >>  8) & 0xFF00)
             | ((v <<  8) & 0xFF0000)
             | ((v << 24) & 0xFF000000u);
    }

    // --- Parse logic ---

    // the tag types the Ethernet model reads: 802.1ad's service tag and 802.1Q's customer tag
    static constexpr bool is_tag(std::uint16_t ethertype) {
        return ethertype == 0x8100 || ethertype == 0x88A8;
    }

    // what a frame read as Ethernet says it carries, where the frame is a cooked capture's instead:
    // a type no Ethernet frame here holds, and an address length of 6 where a cooked header has it
    static constexpr bool is_ethernet(std::uint16_t ethertype) {
        return ethertype == 0x0800 || ethertype == 0x86DD || is_tag(ethertype) || ethertype == 0x9100 || ethertype == 0x0806;
    }

    void parse() {
        // Minimum ethernet frame: 14 bytes (6 dst + 6 src + 2 ethertype)
        if (!data_ || len_ < 14) return;

        auto& ethernet_reader = ethernet();
        auto whole = ethernet_reader.read(data_, len_);
        const auto& frame = ethernet_reader.ethernet_frame;

        if (!is_ethernet(frame.ether_type()) && len_ >= 16) {
            auto& sll_reader = sll();
            auto cooked_whole = sll_reader.read(data_, len_);
            const auto& cooked = sll_reader.sll_frame;

            if (cooked.sll_address_length() == 6) {
                // the C-Tag the model reads after the cooked header (protocol type 8100), its VID kept
                auto ethertype = cooked.sll_protocol_type();
                auto offset = static_cast<std::uint32_t>(16);

                if (cooked.sll_vlan_tag.data != nullptr) {
                    if (cooked.sll_vlan_tag.size < 4) return;
                    vlan_id = cooked.sll_vlan_tag.sll_vlan_id();
                    ethertype = cooked.sll_vlan_tag.sll_inner_protocol_type();
                    offset += 4;
                }

                const auto tagged = offset;
                if (!stacked(ethertype, offset)) return;
                if (ethertype != 0x0800) return;
                if (offset != tagged) cooked_whole = sll_reader.read_ip_packet(data_ + offset, len_ - offset);
                // none where the hardware type says the protocol type is no Ether Type (FRAD, RADIOTAP, NETLINK)
                if (cooked.sll_payload.ip_packet.data == nullptr) return;
                internet(cooked.sll_payload.ip_packet, offset, cooked_whole);
                return;
            }
        }

        // the tags the model reads, the innermost's VID kept
        auto ethertype = frame.ether_type();
        auto offset = static_cast<std::uint32_t>(14);

        if (frame.service_tag.data != nullptr) {
            if (frame.service_tag.size < 4) return;
            vlan_id = frame.service_tag.service_vlan_id();
            ethertype = frame.service_tag.service_inner_ether_type();
            offset += 4;
        }

        if (frame.customer_tag.data != nullptr) {
            if (frame.customer_tag.size < 4) return;
            vlan_id = frame.customer_tag.vlan_id();
            ethertype = frame.customer_tag.customer_inner_ether_type();
            offset += 4;
        }

        const auto read = offset;
        if (!stacked(ethertype, offset)) return;

        // Only IPv4
        if (ethertype != 0x0800) return;
        if (offset != read) whole = ethernet_reader.read_ip_packet(data_ + offset, len_ - offset);
        internet(frame.ethernet_payload.ip_packet, offset, whole);
    }

    // tags stacked beyond those the model reads (a second 802.1Q customer tag), stepped over to the
    // innermost, whose VID is kept; false where the frame ends inside one
    bool stacked(std::uint16_t& ethertype, std::uint32_t& offset) {
        while (is_tag(ethertype)) {
            if (len_ < offset + 4) return false;
            vlan_id = read_u16(data_ + offset) & 0x0FFF;
            ethertype = read_u16(data_ + offset + 2);
            offset += 4;
        }
        return true;
    }

    // the IPv4 packet at offset, as its reader read it, then its UDP datagram or TCP segment
    // (whole: the reader read the packet to its end, so the sizes it worked out are this frame's)
    template <typename Packet>
    void internet(const Packet& ip, std::uint32_t ip_start, bool whole) {
        // IPv4 header: minimum 20 bytes
        ip_start_ = ip_start;
        if (len_ < ip_start + 20) return;

        if (ip.ip_version() != 4) return;

        auto ip_hdr_len = static_cast<std::uint32_t>(ip.ip_header_length()) * 4;
        if (ip_hdr_len < 20) return;
        if (len_ < ip_start + ip_hdr_len) return;

        auto ip_total_len = static_cast<std::uint32_t>(ip.total_length());

        // Clamp to capture length (truncated captures stay valid)
        auto available = len_ - ip_start;
        if (ip_total_len > available) ip_total_len = available;

        ip_protocol = ip.ip_protocol();

        // src_ip and dst_ip in network byte order (raw memcpy)
        std::memcpy(&src_ip, ip.source_address(), 4);
        std::memcpy(&dst_ip, ip.destination_address(), 4);

        auto l4_start = ip_start + ip_hdr_len;
        l4_start_ = l4_start;

        if (ip_protocol == 17) {
            // UDP: 8-byte header
            if (ip_total_len < ip_hdr_len + 8) return;
            if (len_ < l4_start + 8) return;

            const auto& udp = ip.ip_payload.udp_datagram;
            if (udp.data != data_ + l4_start) return;
            src_port = udp.udp_source_port();
            dst_port = udp.udp_destination_port();

            // the datagram as its length states it, cut where the packet ends; none where it states fewer than its header
            payload = udp.udp_payload();
            payload_len = 0;
            if (whole) payload_len = static_cast<std::uint32_t>(udp.udp_payload_size);

        } else if (ip_protocol == 6) {
            // TCP: variable header (minimum 20 bytes)
            if (ip_total_len < ip_hdr_len + 20) return;
            if (len_ < l4_start + 20) return;

            const auto& tcp = ip.ip_payload.tcp_segment;
            if (tcp.data != data_ + l4_start) return;
            src_port = tcp.tcp_source_port();
            dst_port = tcp.tcp_destination_port();
            tcp_seq = tcp.tcp_sequence_number();
            tcp_flags = static_cast<std::uint8_t>(tcp.offset_and_flags() & 0xFF);

            auto tcp_hdr_len = static_cast<std::uint32_t>(tcp.data_offset()) * 4;
            if (tcp_hdr_len < 20) return;
            if (len_ < l4_start + tcp_hdr_len) return;

            // the payload behind the options, as many bytes as the packet has left; none where the options overrun it
            payload = tcp.data + tcp_hdr_len;
            payload_len = 0;
            if (whole) payload_len = static_cast<std::uint32_t>(tcp.tcp_payload_size);
        }
        // Other protocols: payload stays nullptr
    }
};

} // namespace packet