// Asx.AsxDerivatives.Ntp.Itch.v1.05: pcap/readers/Ietf.Pcap.Nanosecond.v2.4/PcapFileReader.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace ietf::pcap::nanosecond::v2_4 {

// Pcap File reader: each part read where the model's rules place it, without copying.
// A struct's data is where it lies, null where it is not there; size is how many bytes it holds,
// or, where reading it failed, how many it got through. Each read function can be called on its own,
// reading with what was read before it.
struct PcapFileReader {

    // a big endian integer
    template <typename Value>
    [[nodiscard]] static Value big(const std::byte* at) noexcept {
        Value value{};
        std::memcpy(&value, at, sizeof(Value));
        if constexpr (std::endian::native == std::endian::little && sizeof(Value) > 1) {
            value = std::byteswap(value);
        }
        return value;
    }

    // a little endian integer
    template <typename Value>
    [[nodiscard]] static Value little(const std::byte* at) noexcept {
        Value value{};
        std::memcpy(&value, at, sizeof(Value));
        if constexpr (std::endian::native == std::endian::big && sizeof(Value) > 1) {
            value = std::byteswap(value);
        }
        return value;
    }

    // a big endian integer of a width C++ has no type for
    [[nodiscard]] static std::uint64_t big(const std::byte* at, std::size_t width) noexcept {
        std::uint64_t value = 0;
        for (std::size_t index = 0; index < width; ++index) {
            value = (value << 8) | std::to_integer<std::uint64_t>(at[index]);
        }
        return value;
    }

    // a little endian integer of a width C++ has no type for
    [[nodiscard]] static std::uint64_t little(const std::byte* at, std::size_t width) noexcept {
        std::uint64_t value = 0;
        for (std::size_t index = width; index > 0; --index) {
            value = (value << 8) | std::to_integer<std::uint64_t>(at[index - 1]);
        }
        return value;
    }

    // Pcap capture file, little endian: a File Header, then one Packet Record per captured packet
    struct PcapFile {
        const std::byte* data = nullptr;
        std::size_t size = 0;

        // Pcap file header: byte order and timestamp resolution, version, snapshot length and link layer
        struct PcapFileHeader {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // Byte order and timestamp resolution of the file: A1B2C3D4 for microseconds, A1B23C4D for nanoseconds
            [[nodiscard]] std::uint32_t magic_number() const noexcept { return little<std::uint32_t>(data + 0); }

            // Major version of the format: 2
            [[nodiscard]] std::uint16_t pcap_major_version() const noexcept { return little<std::uint16_t>(data + 4); }

            // Minor version of the format: 4
            [[nodiscard]] std::uint16_t pcap_minor_version() const noexcept { return little<std::uint16_t>(data + 6); }

            // Not used: should be zero, and ignored by readers (once the gmt to local correction)
            [[nodiscard]] std::uint32_t pcap_reserved1() const noexcept { return little<std::uint32_t>(data + 8); }

            // Not used: should be zero, and ignored by readers (once the accuracy of timestamps)
            [[nodiscard]] std::uint32_t pcap_reserved2() const noexcept { return little<std::uint32_t>(data + 12); }

            // Most octets captured from each packet
            [[nodiscard]] std::uint32_t snap_len() const noexcept { return little<std::uint32_t>(data + 16); }

            // Link layer type of the packets in the file, and whether each carries its frame check sequence
            [[nodiscard]] std::uint32_t link_type_information() const noexcept { return little<std::uint32_t>(data + 20); }
            // Number of 2 octet words of frame check sequence appended to each packet, when Pcap P is set
            [[nodiscard]] std::uint8_t fcs_len() const noexcept { return static_cast<std::uint8_t>((link_type_information() >> 28) & 0xFu); }
            // Set when Fcs Len is present
            [[nodiscard]] bool pcap_p() const noexcept { return ((link_type_information() >> 26) & 1u) != 0; }
            // Link layer type of every packet in the file, from the pcap LinkType registry
            [[nodiscard]] std::uint16_t pcap_link_type() const noexcept { return static_cast<std::uint16_t>((link_type_information() >> 0) & 0xFFFFu); }
        };
        PcapFileHeader pcap_file_header;

        // Pcap packet record: when the packet was captured, its captured and original lengths, then the packet
        struct PcapPacketRecord {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // Seconds elapsed since 1970-01-01 00:00:00 UTC
            [[nodiscard]] std::uint32_t capture_seconds() const noexcept { return little<std::uint32_t>(data + 0 + 0); }
            // Microseconds or nanoseconds elapsed since Capture Seconds, as the Magic Number says
            [[nodiscard]] std::uint32_t capture_fraction() const noexcept { return little<std::uint32_t>(data + 0 + 4); }
            // When the packet was captured: seconds since 1970-01-01 00:00:00 UTC, and the fraction of that second
            [[nodiscard]] std::uint64_t capture_time() const noexcept { return static_cast<std::uint64_t>(capture_seconds()) * UINT64_C(1000000000) + static_cast<std::uint64_t>(capture_fraction()); }

            // Octets captured from the packet: the length of Pcap Packet Data
            [[nodiscard]] std::uint32_t captured_packet_length() const noexcept { return little<std::uint32_t>(data + 8); }

            // Octets of the packet as it was on the wire, before any truncation to the snapshot length
            [[nodiscard]] std::uint32_t original_packet_length() const noexcept { return little<std::uint32_t>(data + 12); }

            // The packet as captured, link layer first
            std::size_t pcap_packet_data_size = 0;
            [[nodiscard]] const std::byte* pcap_packet_data() const noexcept { return data + 16; }
        };
        PcapPacketRecord pcap_packet_record;
        std::size_t pcap_packet_record_count = 0;   // entries read
        std::size_t pcap_packet_record_first = 0;   // where the first lies
    };

    PcapFile pcap_file;

    // read a Pcap File
    bool read(const std::byte* data, std::size_t length) noexcept {
        return read_pcap_file(data, length);
    }

    // Pcap capture file, little endian: a File Header, then one Packet Record per captured packet
    bool read_pcap_file(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcap_file;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Pcap file header: byte order and timestamp resolution, version, snapshot length and link layer
        if (!read_pcap_file_header(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcap_file_header.size;
        // Pcap packet record: when the packet was captured, its captured and original lengths, then the packet
        self.pcap_packet_record.data = nullptr;
        self.pcap_packet_record_count = 0;
        self.pcap_packet_record_first = offset;
        while (offset < limit) {
            if (!read_pcap_packet_record(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcap_packet_record.size == 0) { self.size = offset; return false; }
            offset += self.pcap_packet_record.size;
            ++self.pcap_packet_record_count;
        }
        self.size = offset;
        return true;
    }

    // Pcap file header: byte order and timestamp resolution, version, snapshot length and link layer
    bool read_pcap_file_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcap_file.pcap_file_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Byte order and timestamp resolution of the file: A1B2C3D4 for microseconds, A1B23C4D for nanoseconds
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Major version of the format: 2
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Minor version of the format: 4
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Not used: should be zero, and ignored by readers (once the gmt to local correction)
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Not used: should be zero, and ignored by readers (once the accuracy of timestamps)
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Most octets captured from each packet
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Link layer type of the packets in the file, and whether each carries its frame check sequence
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // Pcap packet record: when the packet was captured, its captured and original lengths, then the packet
    bool read_pcap_packet_record(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcap_file.pcap_packet_record;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // When the packet was captured: seconds since 1970-01-01 00:00:00 UTC, and the fraction of that second
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        // Octets captured from the packet: the length of Pcap Packet Data
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcap_file.pcap_packet_record.captured_packet_length()) + INT64_C(16);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // Octets of the packet as it was on the wire, before any truncation to the snapshot length
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The packet as captured, link layer first
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcap_file.pcap_packet_record.captured_packet_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcap_packet_data_size = bytes;
            offset += bytes;
        }
        self.size = limit;
        return true;
    }

    // the bytes a Pcap Packet Record must hold before its length is known
    static constexpr std::size_t pcap_packet_record_header = 12;

    // how long a Pcap Packet Record is, read from its first pcap_packet_record_header bytes
    [[nodiscard]] static std::int64_t pcap_packet_record_length(const std::byte* at) noexcept {
        return static_cast<std::int64_t>(little<std::uint32_t>(at + 8)) + INT64_C(16);
    }
};

}
