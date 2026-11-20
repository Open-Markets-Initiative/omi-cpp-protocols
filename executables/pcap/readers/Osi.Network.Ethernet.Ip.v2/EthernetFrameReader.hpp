// Asx.AsxDerivatives.Ntp.Itch.v1.05: pcap/readers/Osi.Network.Ethernet.Ip.v2/EthernetFrameReader.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace osi::network::ethernet::ip::v2 {

// Ethernet Frame reader: each part read where the model's rules place it, without copying.
// A struct's data is where it lies, null where it is not there; size is how many bytes it holds,
// or, where reading it failed, how many it got through. Each read function can be called on its own,
// reading with what was read before it.
struct EthernetFrameReader {

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

    // Ethernet II frame: its addresses, what it carries, any 802.1Q tags, and that payload
    struct EthernetFrame {
        const std::byte* data = nullptr;
        std::size_t size = 0;

        // Hardware address the frame is sent to
        static constexpr std::size_t destination_mac_size = 6;
        [[nodiscard]] const std::byte* destination_mac() const noexcept { return data + 0; }

        // Hardware address the frame is sent from
        static constexpr std::size_t source_mac_size = 6;
        [[nodiscard]] const std::byte* source_mac() const noexcept { return data + 6; }

        // The protocol the frame carries, or the tag protocol identifier of a tagged frame (IEEE 802 Numbers, ETHER TYPES)
        [[nodiscard]] std::uint16_t ether_type() const noexcept { return big<std::uint16_t>(data + 12); }

        // IEEE 802.1Q service VLAN tag (S-Tag): the service VLAN and priority, then what follows the tag
        struct ServiceTag {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // S-Tag control information, most significant bit first
            [[nodiscard]] std::uint16_t service_tag_control() const noexcept { return big<std::uint16_t>(data + 0); }
            // Priority code point
            [[nodiscard]] std::uint8_t service_priority() const noexcept { return static_cast<std::uint8_t>((service_tag_control() >> 13) & 0x7u); }
            // Drop eligible indicator
            [[nodiscard]] bool service_drop_eligible() const noexcept { return ((service_tag_control() >> 12) & 1u) != 0; }
            // Service VLAN identifier
            [[nodiscard]] std::uint16_t service_vlan_id() const noexcept { return static_cast<std::uint16_t>((service_tag_control() >> 0) & 0xFFFu); }

            // What follows the S-Tag: the C-Tag protocol identifier (8100), or the protocol the frame carries
            [[nodiscard]] std::uint16_t service_inner_ether_type() const noexcept { return big<std::uint16_t>(data + 2); }
        };
        ServiceTag service_tag;

        // IEEE 802.1Q customer VLAN tag (C-Tag): the VLAN and priority, then the protocol the frame carries
        struct CustomerTag {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // C-Tag control information, most significant bit first
            [[nodiscard]] std::uint16_t customer_tag_control() const noexcept { return big<std::uint16_t>(data + 0); }
            // Priority code point
            [[nodiscard]] std::uint8_t vlan_priority() const noexcept { return static_cast<std::uint8_t>((customer_tag_control() >> 13) & 0x7u); }
            // Drop eligible indicator
            [[nodiscard]] bool drop_eligible() const noexcept { return ((customer_tag_control() >> 12) & 1u) != 0; }
            // VLAN identifier
            [[nodiscard]] std::uint16_t vlan_id() const noexcept { return static_cast<std::uint16_t>((customer_tag_control() >> 0) & 0xFFFu); }

            // The protocol a tagged frame carries
            [[nodiscard]] std::uint16_t customer_inner_ether_type() const noexcept { return big<std::uint16_t>(data + 2); }
        };
        CustomerTag customer_tag;

        // Branch
        struct EthernetPayload {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // Internet Protocol version 4 datagram: its header, then what it carries
            struct IpPacket {
                const std::byte* data = nullptr;
                std::size_t size = 0;

                // The version and the internet header length, most significant bit first
                [[nodiscard]] std::uint8_t version_and_header_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }
                // The format of the internet header: 4
                [[nodiscard]] std::uint8_t ip_version() const noexcept { return static_cast<std::uint8_t>((version_and_header_length() >> 4) & 0xFu); }
                // Internet Header Length (IHL): the length of the internet header in 32 bit words, at least 5
                [[nodiscard]] std::uint8_t ip_header_length() const noexcept { return static_cast<std::uint8_t>((version_and_header_length() >> 0) & 0xFu); }

                // RFC 791's Type of Service octet, as RFC 2474 (DS field) and RFC 3168 (ECN) redefine it, most significant bit first
                [[nodiscard]] std::uint8_t type_of_service() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }
                // Differentiated services code point (RFC 2474); RFC 791 bits 0 to 5: precedence, delay, throughput and reliability
                [[nodiscard]] std::uint8_t differentiated_services() const noexcept { return static_cast<std::uint8_t>((type_of_service() >> 2) & 0x3Fu); }
                // Explicit congestion notification (RFC 3168); RFC 791 bits 6 and 7, reserved
                [[nodiscard]] std::uint8_t congestion_notification() const noexcept { return static_cast<std::uint8_t>((type_of_service() >> 0) & 0x3u); }

                // The length of the datagram in octets, internet header and data
                [[nodiscard]] std::uint16_t total_length() const noexcept { return big<std::uint16_t>(data + 2); }

                // An identifying value assigned by the sender to aid in assembling the fragments of a datagram
                [[nodiscard]] std::uint16_t identification() const noexcept { return big<std::uint16_t>(data + 4); }

                // Control flags and fragment offset, most significant bit first
                [[nodiscard]] std::uint16_t fragmentation() const noexcept { return big<std::uint16_t>(data + 6); }
                // Bit 1 (DF): 0 may fragment, 1 don't fragment
                [[nodiscard]] bool dont_fragment() const noexcept { return ((fragmentation() >> 14) & 1u) != 0; }
                // Bit 2 (MF): 0 last fragment, 1 more fragments
                [[nodiscard]] bool more_fragments() const noexcept { return ((fragmentation() >> 13) & 1u) != 0; }
                // Where in the datagram this fragment belongs, in units of 8 octets; the first fragment has offset zero
                [[nodiscard]] std::uint16_t fragment_offset() const noexcept { return static_cast<std::uint16_t>((fragmentation() >> 0) & 0x1FFFu); }

                // The maximum time the datagram is allowed to remain in the internet system: decreased by at least one by every module that processes it
                [[nodiscard]] std::uint8_t time_to_live() const noexcept { return std::to_integer<std::uint8_t>(*(data + 8)); }

                // The next level protocol used in the data portion of the datagram, from IANA's Assigned Internet Protocol Numbers
                [[nodiscard]] std::uint8_t ip_protocol() const noexcept { return std::to_integer<std::uint8_t>(*(data + 9)); }

                // The 16 bit one's complement of the one's complement sum of all 16 bit words in the header only, computed with this field zero; recomputed wherever the header changes
                [[nodiscard]] std::uint16_t ip_header_checksum() const noexcept { return big<std::uint16_t>(data + 10); }

                // The source address
                static constexpr std::size_t source_address_size = 4;
                [[nodiscard]] const std::byte* source_address() const noexcept { return data + 12; }

                // The destination address; a multicast group for a market data feed
                static constexpr std::size_t destination_address_size = 4;
                [[nodiscard]] const std::byte* destination_address() const noexcept { return data + 16; }

                // The options, and any padding after them: the header past its fixed 20 octets
                struct IpOptions {
                    const std::byte* data = nullptr;
                    std::size_t size = 0;

                    // One option: a single octet of option type, or an option type octet, a length octet and the option data
                    struct IpOption {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The option type octet: copied flag (bit 0), option class (bits 1 and 2) and option number (bits 3 to 7)
                        [[nodiscard]] std::uint8_t ip_option_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Branch
                        struct IpOptionBody {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // DoD Basic Security option (RFC 1108 2): the U.S. classification level at which the datagram is to be protected, and the authorities whose protection rules apply; its length is at least 3, the protection authority flags may be absent
                            struct SecurityOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Octets of the option, counting the option type octet, this length octet and the option data
                                [[nodiscard]] std::uint8_t ip_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // The (U.S.) classification level at which the datagram must be protected (RFC 1108 2.3); a value not in the table, or a reserved one, is in error
                                [[nodiscard]] std::uint8_t classification_level() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // The National Access Programs or Special Access Programs whose protection rules apply (RFC 1108 2.4): the low-order bit of each octet is 0 in the final octet and 1 when more octets follow
                                std::size_t protection_authority_flags_size = 0;
                                [[nodiscard]] const std::byte* protection_authority_flags() const noexcept { return data + 2; }
                            };
                            SecurityOption security_option;

                            // Loose or strict source and record route, or record route: a pointer, then internet addresses
                            struct RouteOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Octets of the option, counting the option type octet, this length octet and the option data
                                [[nodiscard]] std::uint8_t ip_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Octets from the beginning of the option to the next source address to be processed (or the next area to record into), counting from 1; at least 4
                                [[nodiscard]] std::uint8_t route_pointer() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // The route: internet addresses of 32 bits each
                                struct RouteData {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // An internet address on the route
                                    static constexpr std::size_t route_address_width = 4;
                                    std::size_t route_address_count = 0;
                                    [[nodiscard]] const std::byte* route_address(std::size_t index) const noexcept { return data + 0 + index * 4; }
                                };
                                RouteData route_data;
                            };
                            RouteOption route_option;

                            // Stream ID: length 4, a 16 bit SATNET stream identifier
                            struct StreamIdentifierOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Octets of the option, counting the option type octet, this length octet and the option data
                                [[nodiscard]] std::uint8_t ip_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // The SATNET stream identifier
                                [[nodiscard]] std::uint16_t stream_identifier() const noexcept { return big<std::uint16_t>(data + 1); }
                            };
                            StreamIdentifierOption stream_identifier_option;

                            // Internet Timestamp: a pointer, overflow and flag, then timestamps, each preceded by an address when the flag says so
                            struct InternetTimestampOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Octets of the option, counting the option type octet, this length octet and the option data
                                [[nodiscard]] std::uint8_t ip_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Octets from the beginning of the option to the end of the timestamps plus one: the octet beginning the space for the next timestamp; at least 5
                                [[nodiscard]] std::uint8_t timestamp_pointer() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // Overflow and flag, most significant bit first
                                [[nodiscard]] std::uint8_t overflow_and_flag() const noexcept { return std::to_integer<std::uint8_t>(*(data + 2)); }
                                // The number of IP modules that cannot register timestamps for lack of space
                                [[nodiscard]] std::uint8_t timestamp_overflow() const noexcept { return static_cast<std::uint8_t>((overflow_and_flag() >> 4) & 0xFu); }
                                // 0 timestamps only, 1 each timestamp preceded by the registering entity's internet address, 3 the addresses are prespecified
                                [[nodiscard]] std::uint8_t timestamp_flag() const noexcept { return static_cast<std::uint8_t>((overflow_and_flag() >> 0) & 0xFu); }

                                // The timestamp area: 32 bit timestamps in milliseconds since midnight UT, right justified (the high order bit set for a non-standard value), each preceded by a 32 bit internet address when the flag is 1 or 3
                                std::size_t timestamp_data_size = 0;
                                [[nodiscard]] const std::byte* timestamp_data() const noexcept { return data + 3; }
                            };
                            InternetTimestampOption internet_timestamp_option;

                            // An option this model gives no layout: its length, then its data
                            struct IpOtherOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Octets of the option, counting the option type octet, this length octet and the option data
                                [[nodiscard]] std::uint8_t ip_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // The option's data
                                std::size_t ip_option_data_size = 0;
                                [[nodiscard]] const std::byte* ip_option_data() const noexcept { return data + 1; }
                            };
                            IpOtherOption ip_other_option;
                        };
                        IpOptionBody ip_option_body;
                    };
                    IpOption ip_option;
                    std::size_t ip_option_count = 0;   // entries read
                    std::size_t ip_option_first = 0;   // where the first lies
                };
                IpOptions ip_options;

                // Branch
                struct IpPayload {
                    const std::byte* data = nullptr;
                    std::size_t size = 0;

                    // Transmission Control Protocol segment: its ports and stream position, then a piece of the stream
                    struct TcpSegment {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Port the segment is sent from
                        [[nodiscard]] std::uint16_t tcp_source_port() const noexcept { return big<std::uint16_t>(data + 0); }

                        // Port the segment is sent to
                        [[nodiscard]] std::uint16_t tcp_destination_port() const noexcept { return big<std::uint16_t>(data + 2); }

                        // The sequence number of the first data octet in this segment; when Syn is set, the initial sequence number
                        [[nodiscard]] std::uint32_t tcp_sequence_number() const noexcept { return big<std::uint32_t>(data + 4); }

                        // When Ack is set, the next sequence number the sender of the segment expects to receive
                        [[nodiscard]] std::uint32_t acknowledgment_number() const noexcept { return big<std::uint32_t>(data + 8); }

                        // The header length and the control flags, most significant bit first
                        [[nodiscard]] std::uint16_t offset_and_flags() const noexcept { return big<std::uint16_t>(data + 12); }
                        // The number of 32 bit words in the Tcp header, 5 to 15: where the data begins
                        [[nodiscard]] std::uint8_t data_offset() const noexcept { return static_cast<std::uint8_t>((offset_and_flags() >> 12) & 0xFu); }
                        // Accurate ECN (RFC 9768); bit 7, previously NS (Nonce Sum, RFC 3540, now Historic)
                        [[nodiscard]] bool ae_flag() const noexcept { return ((offset_and_flags() >> 8) & 1u) != 0; }
                        // Congestion Window Reduced (RFC 3168)
                        [[nodiscard]] bool cwr_flag() const noexcept { return ((offset_and_flags() >> 7) & 1u) != 0; }
                        // ECN-Echo (RFC 3168)
                        [[nodiscard]] bool ece_flag() const noexcept { return ((offset_and_flags() >> 6) & 1u) != 0; }
                        // Urgent pointer field is significant
                        [[nodiscard]] bool urg_flag() const noexcept { return ((offset_and_flags() >> 5) & 1u) != 0; }
                        // Acknowledgment field is significant
                        [[nodiscard]] bool ack_flag() const noexcept { return ((offset_and_flags() >> 4) & 1u) != 0; }
                        // Push function
                        [[nodiscard]] bool psh_flag() const noexcept { return ((offset_and_flags() >> 3) & 1u) != 0; }
                        // Reset the connection
                        [[nodiscard]] bool rst_flag() const noexcept { return ((offset_and_flags() >> 2) & 1u) != 0; }
                        // Synchronize sequence numbers
                        [[nodiscard]] bool syn_flag() const noexcept { return ((offset_and_flags() >> 1) & 1u) != 0; }
                        // No more data from sender
                        [[nodiscard]] bool fin_flag() const noexcept { return ((offset_and_flags() >> 0) & 1u) != 0; }

                        // Octets, beginning with the one the acknowledgment field indicates, the sender is willing to accept; shifted by the Window Scale option's shift count when scaling is in use
                        [[nodiscard]] std::uint16_t window_size() const noexcept { return big<std::uint16_t>(data + 14); }

                        // Ones' complement of the ones' complement sum of the pseudo header, the Tcp header with its options, and the data, padded to 16 bits; computed with this field zero. Over IPv4 the pseudo header is the source and destination address, zero, protocol and Tcp length (RFC 9293 3.1); over IPv6 it is the source and destination address (the final destination when a Routing header is present), a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1)
                        [[nodiscard]] std::uint16_t tcp_checksum() const noexcept { return big<std::uint16_t>(data + 16); }

                        // Offset from the segment's sequence number to the octet following the urgent data; only interpreted when Urg is set
                        [[nodiscard]] std::uint16_t urgent_pointer() const noexcept { return big<std::uint16_t>(data + 18); }

                        // Tcp options, and any padding after the End of Option List
                        struct TcpOptions {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
                            struct TcpOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The option's kind, from the IANA TCP Option Kind Numbers registry
                                [[nodiscard]] std::uint8_t tcp_option_kind() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Branch
                                struct TcpOptionBody {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // Maximum Segment Size option, sent only with Syn
                                    struct MaximumSegmentSizeOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The maximum receive segment size at the Tcp endpoint that sends this segment
                                        [[nodiscard]] std::uint16_t maximum_segment_size() const noexcept { return big<std::uint16_t>(data + 1); }
                                    };
                                    MaximumSegmentSizeOption maximum_segment_size_option;

                                    // Window Scale option, sent only with Syn
                                    struct WindowScaleOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // Window scale exponent: the sender's receive window is its Window Size shifted left by this many bits, 0 to 14
                                        [[nodiscard]] std::uint8_t shift_count() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }
                                    };
                                    WindowScaleOption window_scale_option;

                                    // SACK-Permitted option: selective acknowledgment may be used once the connection is established, sent only with Syn
                                    struct SackPermittedOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }
                                    };
                                    SackPermittedOption sack_permitted_option;

                                    // SACK option: the non-contiguous blocks of data received and queued; its length is 8 * n + 2 for n blocks
                                    struct SackOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // One contiguous block of data received and queued
                                        struct SackBlock {
                                            const std::byte* data = nullptr;
                                            std::size_t size = 0;

                                            // The first sequence number of the block
                                            [[nodiscard]] std::uint32_t left_edge_of_block() const noexcept { return big<std::uint32_t>(data + 0); }

                                            // The sequence number immediately following the last sequence number of the block
                                            [[nodiscard]] std::uint32_t right_edge_of_block() const noexcept { return big<std::uint32_t>(data + 4); }
                                        };
                                        SackBlock sack_block;
                                        std::size_t sack_block_count = 0;   // entries read
                                        std::size_t sack_block_first = 0;   // where the first lies
                                    };
                                    SackOption sack_option;

                                    // Timestamps option
                                    struct TimestampsOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // TSval: the current value of the sender's timestamp clock
                                        [[nodiscard]] std::uint32_t timestamp_value() const noexcept { return big<std::uint32_t>(data + 1); }

                                        // TSecr: the TSval most recently received from the remote Tcp, when Ack is set
                                        [[nodiscard]] std::uint32_t timestamp_echo_reply() const noexcept { return big<std::uint32_t>(data + 5); }
                                    };
                                    TimestampsOption timestamps_option;

                                    // An option this model gives no layout: its length, then its data
                                    struct TcpOtherOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The option's data
                                        std::size_t tcp_option_data_size = 0;
                                        [[nodiscard]] const std::byte* tcp_option_data() const noexcept { return data + 1; }
                                    };
                                    TcpOtherOption tcp_other_option;
                                };
                                TcpOptionBody tcp_option_body;
                            };
                            TcpOption tcp_option;
                            std::size_t tcp_option_count = 0;   // entries read
                            std::size_t tcp_option_first = 0;   // where the first lies
                        };
                        TcpOptions tcp_options;

                        std::size_t tcp_payload_at = 0;
                        // The segment's data: a piece of the byte stream
                        std::size_t tcp_payload_size = 0;
                        [[nodiscard]] const std::byte* tcp_payload() const noexcept { return data + tcp_payload_at; }
                    };
                    TcpSegment tcp_segment;

                    // User Datagram Protocol datagram: its ports, then what it carries
                    struct UdpDatagram {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Port of the sending process, when meaningful; zero when not used
                        [[nodiscard]] std::uint16_t udp_source_port() const noexcept { return big<std::uint16_t>(data + 0); }

                        // Port the datagram is sent to; a market data feed's channel
                        [[nodiscard]] std::uint16_t udp_destination_port() const noexcept { return big<std::uint16_t>(data + 2); }

                        // Octets of the datagram, this header and the data: at least 8
                        [[nodiscard]] std::uint16_t udp_length() const noexcept { return big<std::uint16_t>(data + 4); }

                        // 16 bit one's complement of the one's complement sum of a pseudo header, the Udp header and the data, padded with zero octets to a multiple of two. Over IPv4 the pseudo header is the source address, destination address, zero, protocol and Udp length (RFC 768); over IPv6 it is the source and destination address, a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1). A computed checksum of zero is transmitted as all ones (RFC 768). All zero when the sender generated no checksum, which IPv4 allows; over IPv6 the checksum is not optional, and a receiver discards a datagram whose checksum is zero (RFC 8200 8.1)
                        [[nodiscard]] std::uint16_t udp_checksum() const noexcept { return big<std::uint16_t>(data + 6); }

                        // The datagram's data
                        std::size_t udp_payload_size = 0;
                        [[nodiscard]] const std::byte* udp_payload() const noexcept { return data + 8; }
                    };
                    UdpDatagram udp_datagram;

                    // Internet Control Message Protocol message: its type, code and checksum, then the body its type gives
                    struct IcmpMessage {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The type of the message, from the IANA ICMP Type Numbers registry
                        [[nodiscard]] std::uint8_t icmp_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Further qualifies the type; each message's description lists the codes RFC 792 gives it
                        [[nodiscard]] std::uint8_t icmp_code() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // The 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type, computed with this field zero; an odd length message is padded with one zero octet for the computation
                        [[nodiscard]] std::uint16_t icmp_checksum() const noexcept { return big<std::uint16_t>(data + 2); }

                        // Branch
                        struct IcmpBody {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // Echo or Echo Reply message: code 0; the data received in the echo message must be returned in the echo reply
                            struct IcmpEchoMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // An identifier to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_identifier() const noexcept { return big<std::uint16_t>(data + 0); }

                                // A sequence number to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_sequence_number() const noexcept { return big<std::uint16_t>(data + 2); }

                                // Data sent in the echo, returned in the reply
                                std::size_t icmp_echo_data_size = 0;
                                [[nodiscard]] const std::byte* icmp_echo_data() const noexcept { return data + 4; }
                            };
                            IcmpEchoMessage icmp_echo_message;

                            // Destination Unreachable message; codes 0 net unreachable, 1 host unreachable, 2 protocol unreachable, 3 port unreachable, 4 fragmentation needed and DF set, 5 source route failed
                            struct IcmpDestinationUnreachableMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Unused: zero
                                static constexpr std::size_t icmp_leading_unused_size = 1;
                                [[nodiscard]] const std::byte* icmp_leading_unused() const noexcept { return data + 0; }

                                // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
                                [[nodiscard]] std::uint8_t icmp_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // The size in octets of the largest datagram that could be forwarded, along the path of the original datagram, without being fragmented at this router: IP header and data, no lower-level headers (RFC 1191 4). Meaningful for code 4 (fragmentation needed and DF set); zero from a router that does not implement RFC 1191
                                [[nodiscard]] std::uint16_t next_hop_mtu() const noexcept { return big<std::uint16_t>(data + 2); }

                                // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
                                std::size_t icmp_original_datagram_size = 0;
                                [[nodiscard]] const std::byte* icmp_original_datagram() const noexcept { return data + 4; }
                            };
                            IcmpDestinationUnreachableMessage icmp_destination_unreachable_message;

                            // Source Quench message (deprecated by RFC 6633); code 0
                            struct IcmpSourceQuenchMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Unused: zero
                                static constexpr std::size_t icmp_unused_size = 4;
                                [[nodiscard]] const std::byte* icmp_unused() const noexcept { return data + 0; }

                                // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
                                std::size_t icmp_original_datagram_size = 0;
                                [[nodiscard]] const std::byte* icmp_original_datagram() const noexcept { return data + 4; }
                            };
                            IcmpSourceQuenchMessage icmp_source_quench_message;

                            // Redirect message; codes 0 redirect datagrams for the network, 1 for the host, 2 for the type of service and network, 3 for the type of service and host
                            struct IcmpRedirectMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Address of the gateway to which traffic for the network specified in the internet destination network field of the original datagram's data should be sent
                                static constexpr std::size_t gateway_internet_address_size = 4;
                                [[nodiscard]] const std::byte* gateway_internet_address() const noexcept { return data + 0; }

                                // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
                                std::size_t icmp_original_datagram_size = 0;
                                [[nodiscard]] const std::byte* icmp_original_datagram() const noexcept { return data + 4; }
                            };
                            IcmpRedirectMessage icmp_redirect_message;

                            // Time Exceeded message; codes 0 time to live exceeded in transit, 1 fragment reassembly time exceeded
                            struct IcmpTimeExceededMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Unused: zero
                                static constexpr std::size_t icmp_leading_unused_size = 1;
                                [[nodiscard]] const std::byte* icmp_leading_unused() const noexcept { return data + 0; }

                                // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
                                [[nodiscard]] std::uint8_t icmp_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // Unused: zero
                                static constexpr std::size_t icmp_trailing_unused_size = 2;
                                [[nodiscard]] const std::byte* icmp_trailing_unused() const noexcept { return data + 2; }

                                // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
                                std::size_t icmp_original_datagram_size = 0;
                                [[nodiscard]] const std::byte* icmp_original_datagram() const noexcept { return data + 4; }
                            };
                            IcmpTimeExceededMessage icmp_time_exceeded_message;

                            // Parameter Problem message; code 0 pointer indicates the error
                            struct IcmpParameterProblemMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // If code is 0, identifies the octet of the original datagram's header where an error was detected
                                [[nodiscard]] std::uint8_t icmp_pointer() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
                                [[nodiscard]] std::uint8_t icmp_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                                // Unused: zero
                                static constexpr std::size_t icmp_trailing_unused_size = 2;
                                [[nodiscard]] const std::byte* icmp_trailing_unused() const noexcept { return data + 2; }

                                // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
                                std::size_t icmp_original_datagram_size = 0;
                                [[nodiscard]] const std::byte* icmp_original_datagram() const noexcept { return data + 4; }
                            };
                            IcmpParameterProblemMessage icmp_parameter_problem_message;

                            // Timestamp or Timestamp Reply message: code 0; each timestamp is 32 bits of milliseconds since midnight UT, or any time with its high order bit set when the time is not available in milliseconds or cannot be given with respect to midnight UT
                            struct IcmpTimestampMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // An identifier to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_identifier() const noexcept { return big<std::uint16_t>(data + 0); }

                                // A sequence number to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_sequence_number() const noexcept { return big<std::uint16_t>(data + 2); }

                                // The time the sender last touched the message before sending it, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
                                [[nodiscard]] std::uint32_t originate_timestamp() const noexcept { return big<std::uint32_t>(data + 4); }

                                // The time the echoer first touched it on receipt, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
                                [[nodiscard]] std::uint32_t receive_timestamp() const noexcept { return big<std::uint32_t>(data + 8); }

                                // The time the echoer last touched the message on sending it, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
                                [[nodiscard]] std::uint32_t transmit_timestamp() const noexcept { return big<std::uint32_t>(data + 12); }
                            };
                            IcmpTimestampMessage icmp_timestamp_message;

                            // Information Request or Information Reply message (deprecated by RFC 6918): code 0
                            struct IcmpInformationMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // An identifier to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_identifier() const noexcept { return big<std::uint16_t>(data + 0); }

                                // A sequence number to aid in matching requests and replies; may be zero
                                [[nodiscard]] std::uint16_t icmp_sequence_number() const noexcept { return big<std::uint16_t>(data + 2); }
                            };
                            IcmpInformationMessage icmp_information_message;

                            // A message this model gives no layout: the rest of the message
                            struct IcmpOtherMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The message's body after the checksum
                                std::size_t icmp_message_data_size = 0;
                                [[nodiscard]] const std::byte* icmp_message_data() const noexcept { return data + 0; }
                            };
                            IcmpOtherMessage icmp_other_message;
                        };
                        IcmpBody icmp_body;
                    };
                    IcmpMessage icmp_message;

                    // A payload this model gives no layout: any other protocol, or a fragment past the first
                    struct IpOtherPayload {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The payload's octets
                        std::size_t ip_other_data_size = 0;
                        [[nodiscard]] const std::byte* ip_other_data() const noexcept { return data + 0; }
                    };
                    IpOtherPayload ip_other_payload;
                };
                IpPayload ip_payload;
            };
            IpPacket ip_packet;

            // Internet Protocol version 6 packet: its header and extension headers, then what it carries
            struct Ipv6Packet {
                const std::byte* data = nullptr;
                std::size_t size = 0;

                // The version, the traffic class and the flow label, most significant bit first
                [[nodiscard]] std::uint32_t ipv6_version_class_and_flow() const noexcept { return big<std::uint32_t>(data + 0); }
                // Internet Protocol version number, 6
                [[nodiscard]] std::uint8_t ipv6_version() const noexcept { return static_cast<std::uint8_t>((ipv6_version_class_and_flow() >> 28) & 0xFu); }
                // The high six bits of the 8 bit Traffic Class: the differentiated services field (RFC 2474, by RFC 8200 section 7)
                [[nodiscard]] std::uint8_t ipv6_differentiated_services() const noexcept { return static_cast<std::uint8_t>((ipv6_version_class_and_flow() >> 22) & 0x3Fu); }
                // The low two bits of the 8 bit Traffic Class: explicit congestion notification (RFC 3168, by RFC 8200 section 7)
                [[nodiscard]] std::uint8_t ipv6_congestion_notification() const noexcept { return static_cast<std::uint8_t>((ipv6_version_class_and_flow() >> 20) & 0x3u); }
                // 20 bit flow label: labels sequences of packets to be treated in the network as a single flow (RFC 6437)
                [[nodiscard]] std::uint32_t flow_label() const noexcept { return static_cast<std::uint32_t>((ipv6_version_class_and_flow() >> 0) & 0xFFFFFu); }

                // Length of the IPv6 payload, the rest of the packet following this header, in octets; extension headers present are part of the payload. Zero in every packet that carries the Jumbo Payload option (RFC 2675 3)
                [[nodiscard]] std::uint16_t ipv6_payload_length() const noexcept { return big<std::uint16_t>(data + 4); }

                // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 6)); }

                // Decremented by 1 by each node that forwards the packet; the packet is discarded when it reaches zero in forwarding
                [[nodiscard]] std::uint8_t hop_limit() const noexcept { return std::to_integer<std::uint8_t>(*(data + 7)); }

                // 128 bit address of the originator of the packet (RFC 4291)
                static constexpr std::size_t ipv6_source_address_size = 16;
                [[nodiscard]] const std::byte* ipv6_source_address() const noexcept { return data + 8; }

                // 128 bit address of the intended recipient of the packet; not the ultimate recipient when a Routing header is present
                static constexpr std::size_t ipv6_destination_address_size = 16;
                [[nodiscard]] const std::byte* ipv6_destination_address() const noexcept { return data + 24; }

                // Branch
                struct Ipv6ExtensionHeader {
                    const std::byte* data = nullptr;
                    std::size_t size = 0;

                    // Hop-by-Hop Options header: options every node along the delivery path may examine (RFC 8200 4.3)
                    struct HopByHopOptionsHeader {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                        [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Length of the Hop-by-Hop Options header in 8 octet units, not including the first 8 octets
                        [[nodiscard]] std::uint8_t hop_by_hop_hdr_ext_len() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // The header's TLV encoded options, to the header's end
                        struct HopByHopOptions {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // One option: its type, then its data length and data for every type but Pad1
                            struct Ipv6Option {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The option's full 8 bit type: the high 2 bits say what a node that does not recognize it must do, the third whether its data may change en route (IANA Destination Options and Hop-by-Hop Options)
                                [[nodiscard]] std::uint8_t ipv6_option_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // An option's data length and its data
                                struct Ipv6TlvOption {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // Length of the Option Data field of this option, in octets
                                    [[nodiscard]] std::uint8_t opt_data_len() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                    // Option type specific data; for PadN, zero octets
                                    std::size_t ipv6_option_data_size = 0;
                                    [[nodiscard]] const std::byte* ipv6_option_data() const noexcept { return data + 1; }
                                };
                                Ipv6TlvOption ipv6_tlv_option;
                            };
                            Ipv6Option ipv6_option;
                            std::size_t ipv6_option_count = 0;   // entries read
                            std::size_t ipv6_option_first = 0;   // where the first lies
                        };
                        HopByHopOptions hop_by_hop_options;
                    };
                    HopByHopOptionsHeader hop_by_hop_options_header;

                    // Routing header: intermediate nodes to be visited on the way to the packet's destination (RFC 8200 4.4)
                    struct RoutingHeader {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                        [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Length of the Routing header in 8 octet units, not including the first 8 octets
                        [[nodiscard]] std::uint8_t routing_hdr_ext_len() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // Identifier of a particular Routing header variant
                        [[nodiscard]] std::uint8_t routing_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 2)); }

                        // Number of explicitly listed intermediate nodes still to be visited before reaching the final destination
                        [[nodiscard]] std::uint8_t segments_left() const noexcept { return std::to_integer<std::uint8_t>(*(data + 3)); }

                        // Data of the format the Routing Type determines, of length such that the header is a multiple of 8 octets
                        std::size_t routing_type_specific_data_size = 0;
                        [[nodiscard]] const std::byte* routing_type_specific_data() const noexcept { return data + 4; }
                    };
                    RoutingHeader routing_header;

                    // Fragment header: one fragment of a packet the source divided to fit the path MTU (RFC 8200 4.5); its Next Header names the initial header type of the Fragmentable Part of the original packet
                    struct FragmentHeader {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                        [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Reserved: initialized to zero for transmission, ignored on reception
                        static constexpr std::size_t fragment_reserved_size = 1;
                        [[nodiscard]] const std::byte* fragment_reserved() const noexcept { return data + 1; }

                        // The fragment offset, two reserved bits and the M flag, most significant bit first
                        [[nodiscard]] std::uint16_t fragment_offset_and_flag() const noexcept { return big<std::uint16_t>(data + 2); }
                        // The offset, in 8 octet units, of the data following this header, relative to the start of the Fragmentable Part of the original packet
                        [[nodiscard]] std::uint16_t ipv6_fragment_offset() const noexcept { return static_cast<std::uint16_t>((fragment_offset_and_flag() >> 3) & 0x1FFFu); }
                        // M flag: 1 more fragments, 0 last fragment
                        [[nodiscard]] bool more_fragments_flag() const noexcept { return ((fragment_offset_and_flag() >> 0) & 1u) != 0; }

                        // Identifies the fragments of one original packet: different from that of any other fragmented packet sent recently with the same source and destination addresses
                        [[nodiscard]] std::uint32_t fragment_identification() const noexcept { return big<std::uint32_t>(data + 4); }
                    };
                    FragmentHeader fragment_header;

                    // IP Authentication Header: integrity and data origin authentication for the packet (RFC 4302 2); its length is measured in 32 bit words, not the 64 bit words of the other extension headers
                    struct AuthenticationHeader {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                        [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Length of the Authentication Header in 32 bit words (4 octet units), minus 2 (RFC 4302 2.2)
                        [[nodiscard]] std::uint8_t ah_payload_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // Reserved for future use: set to zero by the sender, ignored by the recipient (RFC 4302 2.3)
                        static constexpr std::size_t ah_reserved_size = 2;
                        [[nodiscard]] const std::byte* ah_reserved() const noexcept { return data + 2; }

                        // SPI: an arbitrary 32 bit value a receiver uses to identify the security association to which an incoming packet is bound (RFC 4302 2.4)
                        [[nodiscard]] std::uint32_t security_parameters_index() const noexcept { return big<std::uint32_t>(data + 4); }

                        // An unsigned 32 bit counter, the low-order 32 bits of the packet's sequence number, increasing by one for each packet sent on the security association (RFC 4302 2.5)
                        [[nodiscard]] std::uint32_t ah_sequence_number() const noexcept { return big<std::uint32_t>(data + 8); }

                        // The Integrity Check Value for this packet, with any padding that makes the header a multiple of 8 octets over IPv6 (RFC 4302 2.6)
                        std::size_t integrity_check_value_size = 0;
                        [[nodiscard]] const std::byte* integrity_check_value() const noexcept { return data + 12; }
                    };
                    AuthenticationHeader authentication_header;

                    // Destination Options header: options examined only by the packet's destination node(s) (RFC 8200 4.6)
                    struct DestinationOptionsHeader {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
                        [[nodiscard]] std::uint8_t ipv6_next_header() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Length of the Destination Options header in 8 octet units, not including the first 8 octets
                        [[nodiscard]] std::uint8_t destination_options_hdr_ext_len() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // The header's TLV encoded options, to the header's end
                        struct DestinationOptions {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // One option: its type, then its data length and data for every type but Pad1
                            struct Ipv6Option {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The option's full 8 bit type: the high 2 bits say what a node that does not recognize it must do, the third whether its data may change en route (IANA Destination Options and Hop-by-Hop Options)
                                [[nodiscard]] std::uint8_t ipv6_option_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // An option's data length and its data
                                struct Ipv6TlvOption {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // Length of the Option Data field of this option, in octets
                                    [[nodiscard]] std::uint8_t opt_data_len() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                    // Option type specific data; for PadN, zero octets
                                    std::size_t ipv6_option_data_size = 0;
                                    [[nodiscard]] const std::byte* ipv6_option_data() const noexcept { return data + 1; }
                                };
                                Ipv6TlvOption ipv6_tlv_option;
                            };
                            Ipv6Option ipv6_option;
                            std::size_t ipv6_option_count = 0;   // entries read
                            std::size_t ipv6_option_first = 0;   // where the first lies
                        };
                        DestinationOptions destination_options;
                    };
                    DestinationOptionsHeader destination_options_header;
                };
                Ipv6ExtensionHeader ipv6_extension_header;
                std::size_t ipv6_extension_header_count = 0;   // entries read
                std::size_t ipv6_extension_header_first = 0;   // where the first lies

                // Branch
                struct Ipv6Payload {
                    const std::byte* data = nullptr;
                    std::size_t size = 0;

                    // Transmission Control Protocol segment: its ports and stream position, then a piece of the stream
                    struct TcpSegment {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Port the segment is sent from
                        [[nodiscard]] std::uint16_t tcp_source_port() const noexcept { return big<std::uint16_t>(data + 0); }

                        // Port the segment is sent to
                        [[nodiscard]] std::uint16_t tcp_destination_port() const noexcept { return big<std::uint16_t>(data + 2); }

                        // The sequence number of the first data octet in this segment; when Syn is set, the initial sequence number
                        [[nodiscard]] std::uint32_t tcp_sequence_number() const noexcept { return big<std::uint32_t>(data + 4); }

                        // When Ack is set, the next sequence number the sender of the segment expects to receive
                        [[nodiscard]] std::uint32_t acknowledgment_number() const noexcept { return big<std::uint32_t>(data + 8); }

                        // The header length and the control flags, most significant bit first
                        [[nodiscard]] std::uint16_t offset_and_flags() const noexcept { return big<std::uint16_t>(data + 12); }
                        // The number of 32 bit words in the Tcp header, 5 to 15: where the data begins
                        [[nodiscard]] std::uint8_t data_offset() const noexcept { return static_cast<std::uint8_t>((offset_and_flags() >> 12) & 0xFu); }
                        // Accurate ECN (RFC 9768); bit 7, previously NS (Nonce Sum, RFC 3540, now Historic)
                        [[nodiscard]] bool ae_flag() const noexcept { return ((offset_and_flags() >> 8) & 1u) != 0; }
                        // Congestion Window Reduced (RFC 3168)
                        [[nodiscard]] bool cwr_flag() const noexcept { return ((offset_and_flags() >> 7) & 1u) != 0; }
                        // ECN-Echo (RFC 3168)
                        [[nodiscard]] bool ece_flag() const noexcept { return ((offset_and_flags() >> 6) & 1u) != 0; }
                        // Urgent pointer field is significant
                        [[nodiscard]] bool urg_flag() const noexcept { return ((offset_and_flags() >> 5) & 1u) != 0; }
                        // Acknowledgment field is significant
                        [[nodiscard]] bool ack_flag() const noexcept { return ((offset_and_flags() >> 4) & 1u) != 0; }
                        // Push function
                        [[nodiscard]] bool psh_flag() const noexcept { return ((offset_and_flags() >> 3) & 1u) != 0; }
                        // Reset the connection
                        [[nodiscard]] bool rst_flag() const noexcept { return ((offset_and_flags() >> 2) & 1u) != 0; }
                        // Synchronize sequence numbers
                        [[nodiscard]] bool syn_flag() const noexcept { return ((offset_and_flags() >> 1) & 1u) != 0; }
                        // No more data from sender
                        [[nodiscard]] bool fin_flag() const noexcept { return ((offset_and_flags() >> 0) & 1u) != 0; }

                        // Octets, beginning with the one the acknowledgment field indicates, the sender is willing to accept; shifted by the Window Scale option's shift count when scaling is in use
                        [[nodiscard]] std::uint16_t window_size() const noexcept { return big<std::uint16_t>(data + 14); }

                        // Ones' complement of the ones' complement sum of the pseudo header, the Tcp header with its options, and the data, padded to 16 bits; computed with this field zero. Over IPv4 the pseudo header is the source and destination address, zero, protocol and Tcp length (RFC 9293 3.1); over IPv6 it is the source and destination address (the final destination when a Routing header is present), a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1)
                        [[nodiscard]] std::uint16_t tcp_checksum() const noexcept { return big<std::uint16_t>(data + 16); }

                        // Offset from the segment's sequence number to the octet following the urgent data; only interpreted when Urg is set
                        [[nodiscard]] std::uint16_t urgent_pointer() const noexcept { return big<std::uint16_t>(data + 18); }

                        // Tcp options, and any padding after the End of Option List
                        struct TcpOptions {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
                            struct TcpOption {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The option's kind, from the IANA TCP Option Kind Numbers registry
                                [[nodiscard]] std::uint8_t tcp_option_kind() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Branch
                                struct TcpOptionBody {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // Maximum Segment Size option, sent only with Syn
                                    struct MaximumSegmentSizeOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The maximum receive segment size at the Tcp endpoint that sends this segment
                                        [[nodiscard]] std::uint16_t maximum_segment_size() const noexcept { return big<std::uint16_t>(data + 1); }
                                    };
                                    MaximumSegmentSizeOption maximum_segment_size_option;

                                    // Window Scale option, sent only with Syn
                                    struct WindowScaleOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // Window scale exponent: the sender's receive window is its Window Size shifted left by this many bits, 0 to 14
                                        [[nodiscard]] std::uint8_t shift_count() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }
                                    };
                                    WindowScaleOption window_scale_option;

                                    // SACK-Permitted option: selective acknowledgment may be used once the connection is established, sent only with Syn
                                    struct SackPermittedOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }
                                    };
                                    SackPermittedOption sack_permitted_option;

                                    // SACK option: the non-contiguous blocks of data received and queued; its length is 8 * n + 2 for n blocks
                                    struct SackOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // One contiguous block of data received and queued
                                        struct SackBlock {
                                            const std::byte* data = nullptr;
                                            std::size_t size = 0;

                                            // The first sequence number of the block
                                            [[nodiscard]] std::uint32_t left_edge_of_block() const noexcept { return big<std::uint32_t>(data + 0); }

                                            // The sequence number immediately following the last sequence number of the block
                                            [[nodiscard]] std::uint32_t right_edge_of_block() const noexcept { return big<std::uint32_t>(data + 4); }
                                        };
                                        SackBlock sack_block;
                                        std::size_t sack_block_count = 0;   // entries read
                                        std::size_t sack_block_first = 0;   // where the first lies
                                    };
                                    SackOption sack_option;

                                    // Timestamps option
                                    struct TimestampsOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // TSval: the current value of the sender's timestamp clock
                                        [[nodiscard]] std::uint32_t timestamp_value() const noexcept { return big<std::uint32_t>(data + 1); }

                                        // TSecr: the TSval most recently received from the remote Tcp, when Ack is set
                                        [[nodiscard]] std::uint32_t timestamp_echo_reply() const noexcept { return big<std::uint32_t>(data + 5); }
                                    };
                                    TimestampsOption timestamps_option;

                                    // An option this model gives no layout: its length, then its data
                                    struct TcpOtherOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Octets of the option: its kind, this length and its data
                                        [[nodiscard]] std::uint8_t tcp_option_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The option's data
                                        std::size_t tcp_option_data_size = 0;
                                        [[nodiscard]] const std::byte* tcp_option_data() const noexcept { return data + 1; }
                                    };
                                    TcpOtherOption tcp_other_option;
                                };
                                TcpOptionBody tcp_option_body;
                            };
                            TcpOption tcp_option;
                            std::size_t tcp_option_count = 0;   // entries read
                            std::size_t tcp_option_first = 0;   // where the first lies
                        };
                        TcpOptions tcp_options;

                        std::size_t tcp_payload_at = 0;
                        // The segment's data: a piece of the byte stream
                        std::size_t tcp_payload_size = 0;
                        [[nodiscard]] const std::byte* tcp_payload() const noexcept { return data + tcp_payload_at; }
                    };
                    TcpSegment tcp_segment;

                    // User Datagram Protocol datagram: its ports, then what it carries
                    struct UdpDatagram {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Port of the sending process, when meaningful; zero when not used
                        [[nodiscard]] std::uint16_t udp_source_port() const noexcept { return big<std::uint16_t>(data + 0); }

                        // Port the datagram is sent to; a market data feed's channel
                        [[nodiscard]] std::uint16_t udp_destination_port() const noexcept { return big<std::uint16_t>(data + 2); }

                        // Octets of the datagram, this header and the data: at least 8
                        [[nodiscard]] std::uint16_t udp_length() const noexcept { return big<std::uint16_t>(data + 4); }

                        // 16 bit one's complement of the one's complement sum of a pseudo header, the Udp header and the data, padded with zero octets to a multiple of two. Over IPv4 the pseudo header is the source address, destination address, zero, protocol and Udp length (RFC 768); over IPv6 it is the source and destination address, a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1). A computed checksum of zero is transmitted as all ones (RFC 768). All zero when the sender generated no checksum, which IPv4 allows; over IPv6 the checksum is not optional, and a receiver discards a datagram whose checksum is zero (RFC 8200 8.1)
                        [[nodiscard]] std::uint16_t udp_checksum() const noexcept { return big<std::uint16_t>(data + 6); }

                        // The datagram's data
                        std::size_t udp_payload_size = 0;
                        [[nodiscard]] const std::byte* udp_payload() const noexcept { return data + 8; }
                    };
                    UdpDatagram udp_datagram;

                    // Internet Control Message Protocol for IPv6 message: its type, code and checksum, then the body its type gives
                    struct Icmpv6Message {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The type of the message, from the IANA ICMPv6 type registry: 0 to 127 error messages, 128 to 255 informational messages
                        [[nodiscard]] std::uint8_t icmpv6_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                        // Depends on the message type: an additional level of message granularity; each message's description lists the codes RFC 4443 gives it
                        [[nodiscard]] std::uint8_t icmpv6_code() const noexcept { return std::to_integer<std::uint8_t>(*(data + 1)); }

                        // The 16 bit one's complement of the one's complement sum of the entire ICMPv6 message, starting with the type field, prepended with the IPv6 pseudo header (source and destination address, upper layer packet length, zero, next header 58), computed with this field zero
                        [[nodiscard]] std::uint16_t icmpv6_checksum() const noexcept { return big<std::uint16_t>(data + 2); }

                        // Branch
                        struct Icmpv6Body {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // Destination Unreachable message; codes 0 no route to destination, 1 communication with destination administratively prohibited, 2 beyond scope of source address, 3 address unreachable, 4 port unreachable, 5 source address failed ingress/egress policy, 6 reject route to destination
                            struct Icmpv6DestinationUnreachableMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Length of the padded original datagram field, in 64 bit words (RFC 4884 4.4, 4.5); zero when the message carries no extensions (RFC 4884 5.4)
                                [[nodiscard]] std::uint8_t icmpv6_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Unused: zero when sent, ignored by the receiver
                                static constexpr std::size_t icmpv6_length_unused_size = 3;
                                [[nodiscard]] const std::byte* icmpv6_length_unused() const noexcept { return data + 1; }

                                // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
                                std::size_t icmpv6_invoking_packet_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_invoking_packet() const noexcept { return data + 4; }
                            };
                            Icmpv6DestinationUnreachableMessage icmpv6_destination_unreachable_message;

                            // Packet Too Big message; code set to 0 by the originator and ignored by the receiver
                            struct Icmpv6PacketTooBigMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The Maximum Transmission Unit of the next-hop link
                                [[nodiscard]] std::uint32_t mtu() const noexcept { return big<std::uint32_t>(data + 0); }

                                // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
                                std::size_t icmpv6_invoking_packet_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_invoking_packet() const noexcept { return data + 4; }
                            };
                            Icmpv6PacketTooBigMessage icmpv6_packet_too_big_message;

                            // Time Exceeded message; codes 0 hop limit exceeded in transit, 1 fragment reassembly time exceeded
                            struct Icmpv6TimeExceededMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Length of the padded original datagram field, in 64 bit words (RFC 4884 4.4, 4.5); zero when the message carries no extensions (RFC 4884 5.4)
                                [[nodiscard]] std::uint8_t icmpv6_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                // Unused: zero when sent, ignored by the receiver
                                static constexpr std::size_t icmpv6_length_unused_size = 3;
                                [[nodiscard]] const std::byte* icmpv6_length_unused() const noexcept { return data + 1; }

                                // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
                                std::size_t icmpv6_invoking_packet_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_invoking_packet() const noexcept { return data + 4; }
                            };
                            Icmpv6TimeExceededMessage icmpv6_time_exceeded_message;

                            // Parameter Problem message; codes 0 erroneous header field encountered, 1 unrecognized Next Header type encountered, 2 unrecognized IPv6 option encountered
                            struct Icmpv6ParameterProblemMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The octet offset within the invoking packet where the error was detected; beyond the end of the ICMPv6 packet when the field in error does not fit in an ICMPv6 error message
                                [[nodiscard]] std::uint32_t icmpv6_pointer() const noexcept { return big<std::uint32_t>(data + 0); }

                                // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
                                std::size_t icmpv6_invoking_packet_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_invoking_packet() const noexcept { return data + 4; }
                            };
                            Icmpv6ParameterProblemMessage icmpv6_parameter_problem_message;

                            // Echo Request or Echo Reply message: code 0; the reply's identifier, sequence number and data are those of the request
                            struct Icmpv6EchoMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // An identifier to aid in matching Echo Replies to this Echo Request; may be zero
                                [[nodiscard]] std::uint16_t icmpv6_identifier() const noexcept { return big<std::uint16_t>(data + 0); }

                                // A sequence number to aid in matching Echo Replies to this Echo Request; may be zero
                                [[nodiscard]] std::uint16_t icmpv6_sequence_number() const noexcept { return big<std::uint16_t>(data + 2); }

                                // Zero or more octets of arbitrary data; a reply carries the request's data
                                std::size_t icmpv6_echo_data_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_echo_data() const noexcept { return data + 4; }
                            };
                            Icmpv6EchoMessage icmpv6_echo_message;

                            // A message this model gives no layout: the rest of the message
                            struct Icmpv6OtherMessage {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // The message's body after the checksum
                                std::size_t icmpv6_message_data_size = 0;
                                [[nodiscard]] const std::byte* icmpv6_message_data() const noexcept { return data + 0; }
                            };
                            Icmpv6OtherMessage icmpv6_other_message;
                        };
                        Icmpv6Body icmpv6_body;
                    };
                    Icmpv6Message icmpv6_message;

                    // A payload this model gives no layout: any other next header (59 no next header, 50 Encapsulating Security Payload), or a fragment past the first
                    struct Ipv6OtherPayload {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The payload's octets
                        std::size_t ipv6_other_data_size = 0;
                        [[nodiscard]] const std::byte* ipv6_other_data() const noexcept { return data + 0; }
                    };
                    Ipv6OtherPayload ipv6_other_payload;
                };
                Ipv6Payload ipv6_payload;
            };
            Ipv6Packet ipv6_packet;

            // A payload this model gives no layout: any other Ether Type (Arp, Lldp, ...)
            struct EthernetOtherPayload {
                const std::byte* data = nullptr;
                std::size_t size = 0;

                // The payload's octets
                std::size_t ethernet_other_data_size = 0;
                [[nodiscard]] const std::byte* ethernet_other_data() const noexcept { return data + 0; }
            };
            EthernetOtherPayload ethernet_other_payload;
        };
        EthernetPayload ethernet_payload;
    };

    EthernetFrame ethernet_frame;

    // the value each stored identifier kept last
    std::uint64_t stored_ipv6_fragment_offset = 0;
    bool has_stored_ipv6_fragment_offset = false;
    std::uint64_t stored_ipv6_next_header = 0;
    bool has_stored_ipv6_next_header = false;

    // read a Ethernet Frame
    bool read(const std::byte* data, std::size_t length) noexcept {
        has_stored_ipv6_fragment_offset = false;
        has_stored_ipv6_next_header = false;
        return read_ethernet_frame(data, length);
    }

    // Ethernet II frame: its addresses, what it carries, any 802.1Q tags, and that payload
    bool read_ethernet_frame(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Hardware address the frame is sent to
        if (offset + 6 > limit) { self.size = offset; return false; }
        offset += 6;
        // Hardware address the frame is sent from
        if (offset + 6 > limit) { self.size = offset; return false; }
        offset += 6;
        // The protocol the frame carries, or the tag protocol identifier of a tagged frame (IEEE 802 Numbers, ETHER TYPES)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // IEEE 802.1Q service VLAN tag (S-Tag): the service VLAN and priority, then what follows the tag
        if ((static_cast<std::uint64_t>(this->ethernet_frame.ether_type()) == UINT64_C(34984))) {
            if (!read_service_tag(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.service_tag.size;
        } else {
            self.service_tag.data = nullptr;
        }
        // IEEE 802.1Q customer VLAN tag (C-Tag): the VLAN and priority, then the protocol the frame carries
        if ((static_cast<std::uint64_t>(this->ethernet_frame.ether_type()) == UINT64_C(33024)) || (this->ethernet_frame.service_tag.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.service_tag.service_inner_ether_type()) == UINT64_C(33024))) {
            if (!read_customer_tag(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.customer_tag.size;
        } else {
            self.customer_tag.data = nullptr;
        }
        // Branch
        if (!read_ethernet_payload(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.ethernet_payload.size;
        self.size = offset;
        return true;
    }

    // IEEE 802.1Q service VLAN tag (S-Tag): the service VLAN and priority, then what follows the tag
    bool read_service_tag(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.service_tag;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // S-Tag control information, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // What follows the S-Tag: the C-Tag protocol identifier (8100), or the protocol the frame carries
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // IEEE 802.1Q customer VLAN tag (C-Tag): the VLAN and priority, then the protocol the frame carries
    bool read_customer_tag(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.customer_tag;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // C-Tag control information, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The protocol a tagged frame carries
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ethernet_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.ip_packet.data = nullptr;
        self.ipv6_packet.data = nullptr;
        self.ethernet_other_payload.data = nullptr;
        if ((static_cast<std::uint64_t>(this->ethernet_frame.ether_type()) == UINT64_C(2048)) || (this->ethernet_frame.service_tag.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.service_tag.service_inner_ether_type()) == UINT64_C(2048)) || (this->ethernet_frame.customer_tag.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.customer_tag.customer_inner_ether_type()) == UINT64_C(2048))) {
            if (!read_ip_packet(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        if ((static_cast<std::uint64_t>(this->ethernet_frame.ether_type()) == UINT64_C(34525)) || (this->ethernet_frame.service_tag.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.service_tag.service_inner_ether_type()) == UINT64_C(34525)) || (this->ethernet_frame.customer_tag.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.customer_tag.customer_inner_ether_type()) == UINT64_C(34525))) {
            if (!read_ipv6_packet(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        {
            if (!read_ethernet_other_payload(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
    }

    // Internet Protocol version 4 datagram: its header, then what it carries
    bool read_ip_packet(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The version and the internet header length, most significant bit first
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // RFC 791's Type of Service octet, as RFC 2474 (DS field) and RFC 3168 (ECN) redefine it, most significant bit first
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The length of the datagram in octets, internet header and data
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.total_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // An identifying value assigned by the sender to aid in assembling the fragments of a datagram
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Control flags and fragment offset, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The maximum time the datagram is allowed to remain in the internet system: decreased by at least one by every module that processes it
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The next level protocol used in the data portion of the datagram, from IANA's Assigned Internet Protocol Numbers
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The 16 bit one's complement of the one's complement sum of all 16 bit words in the header only, computed with this field zero; recomputed wherever the header changes
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The source address
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The destination address; a multicast group for a market data feed
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The options, and any padding after them: the header past its fixed 20 octets
        // stepped over at its size; its entries are read on asking (read_ip_option)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_header_length()) * INT64_C(4) - INT64_C(20);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.ip_options.data = at + offset;
            self.ip_options.size = bytes;
            offset += bytes;
        }
        // Branch
        if (!read_ip_payload(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.ip_payload.size;
        self.size = limit;
        return true;
    }

    // The options, and any padding after them: the header past its fixed 20 octets
    bool read_ip_options(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_header_length()) * INT64_C(4) - INT64_C(20);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // One option: a single octet of option type, or an option type octet, a length octet and the option data
        self.ip_option.data = nullptr;
        self.ip_option_count = 0;
        self.ip_option_first = offset;
        while (offset < limit) {
            if (!read_ip_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.ip_option.size == 0) { self.size = offset; return false; }
            offset += self.ip_option.size;
            ++self.ip_option_count;
        }
        self.size = limit;
        return true;
    }

    // One option: a single octet of option type, or an option type octet, a length octet and the option data
    bool read_ip_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option type octet: copied flag (bit 0), option class (bits 1 and 2) and option number (bits 3 to 7)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Branch
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) != UINT64_C(0)) && (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) != UINT64_C(1))) {
            if (!read_ip_option_body(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.ip_option_body.size;
        } else {
            self.ip_option_body.data = nullptr;
        }
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ip_option_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.security_option.data = nullptr;
        self.route_option.data = nullptr;
        self.stream_identifier_option.data = nullptr;
        self.internet_timestamp_option.data = nullptr;
        self.ip_other_option.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(130))) {
            if (!read_security_option(at, limit)) { return false; }
            self.size = self.security_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(131)) || (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(137)) || (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(7))) {
            if (!read_route_option(at, limit)) { return false; }
            self.size = self.route_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(136))) {
            if (!read_stream_identifier_option(at, limit)) { return false; }
            self.size = self.stream_identifier_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_type()) == UINT64_C(68))) {
            if (!read_internet_timestamp_option(at, limit)) { return false; }
            self.size = self.internet_timestamp_option.size;
            return true;
        }
        {
            if (!read_ip_other_option(at, limit)) { return false; }
            self.size = self.ip_other_option.size;
            return true;
        }
    }

    // DoD Basic Security option (RFC 1108 2): the U.S. classification level at which the datagram is to be protected, and the authorities whose protection rules apply; its length is at least 3, the protection authority flags may be absent
    bool read_security_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.security_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option, counting the option type octet, this length octet and the option data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The (U.S.) classification level at which the datagram must be protected (RFC 1108 2.3); a value not in the table, or a reserved one, is in error
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The National Access Programs or Special Access Programs whose protection rules apply (RFC 1108 2.4): the low-order bit of each octet is 0 in the final octet and 1 when more octets follow
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.security_option.ip_option_length()) - INT64_C(3);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.protection_authority_flags_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Loose or strict source and record route, or record route: a pointer, then internet addresses
    bool read_route_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.route_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option, counting the option type octet, this length octet and the option data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Octets from the beginning of the option to the next source address to be processed (or the next area to record into), counting from 1; at least 4
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The route: internet addresses of 32 bits each
        // stepped over at its size; its entries are read on asking ()
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.route_option.ip_option_length()) - INT64_C(3);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.route_data.data = at + offset;
            self.route_data.size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The route: internet addresses of 32 bits each
    bool read_route_data(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.route_option.route_data;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.route_option.ip_option_length()) - INT64_C(3);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // An internet address on the route
        self.route_address_count = (limit - offset) / 4;
        offset += self.route_address_count * 4;
        self.size = limit;
        return true;
    }

    // Stream ID: length 4, a 16 bit SATNET stream identifier
    bool read_stream_identifier_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.stream_identifier_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option, counting the option type octet, this length octet and the option data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The SATNET stream identifier
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // Internet Timestamp: a pointer, overflow and flag, then timestamps, each preceded by an address when the flag says so
    bool read_internet_timestamp_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.internet_timestamp_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option, counting the option type octet, this length octet and the option data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Octets from the beginning of the option to the end of the timestamps plus one: the octet beginning the space for the next timestamp; at least 5
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Overflow and flag, most significant bit first
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The timestamp area: 32 bit timestamps in milliseconds since midnight UT, right justified (the high order bit set for a non-standard value), each preceded by a 32 bit internet address when the flag is 1 or 3
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.internet_timestamp_option.ip_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.timestamp_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // An option this model gives no layout: its length, then its data
    bool read_ip_other_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.ip_other_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option, counting the option type octet, this length octet and the option data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The option's data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_options.ip_option.ip_option_body.ip_other_option.ip_option_length()) - INT64_C(2);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.ip_option_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ip_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.tcp_segment.data = nullptr;
        self.udp_datagram.data = nullptr;
        self.icmp_message.data = nullptr;
        self.ip_other_payload.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_protocol()) == UINT64_C(6)) && (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.fragment_offset()) == UINT64_C(0))) {
            if (!read_ip_payload_tcp_segment(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_protocol()) == UINT64_C(17)) && (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.fragment_offset()) == UINT64_C(0))) {
            if (!read_ip_payload_udp_datagram(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_protocol()) == UINT64_C(1)) && (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.fragment_offset()) == UINT64_C(0))) {
            if (!read_icmp_message(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        {
            if (!read_ip_other_payload(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
    }

    // Transmission Control Protocol segment: its ports and stream position, then a piece of the stream
    bool read_ip_payload_tcp_segment(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Port the segment is sent from
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Port the segment is sent to
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The sequence number of the first data octet in this segment; when Syn is set, the initial sequence number
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // When Ack is set, the next sequence number the sender of the segment expects to receive
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The header length and the control flags, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets, beginning with the one the acknowledgment field indicates, the sender is willing to accept; shifted by the Window Scale option's shift count when scaling is in use
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Ones' complement of the ones' complement sum of the pseudo header, the Tcp header with its options, and the data, padded to 16 bits; computed with this field zero. Over IPv4 the pseudo header is the source and destination address, zero, protocol and Tcp length (RFC 9293 3.1); over IPv6 it is the source and destination address (the final destination when a Routing header is present), a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Offset from the segment's sequence number to the octet following the urgent data; only interpreted when Urg is set
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Tcp options, and any padding after the End of Option List
        // stepped over at its size; its entries are read on asking (read_ip_payload_tcp_option)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data_offset()) * INT64_C(4) - INT64_C(20);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.tcp_options.data = at + offset;
            self.tcp_options.size = bytes;
            offset += bytes;
        }
        // The segment's data: a piece of the byte stream
        self.tcp_payload_at = offset; self.tcp_payload_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Tcp options, and any padding after the End of Option List
    bool read_ip_payload_tcp_options(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data_offset()) * INT64_C(4) - INT64_C(20);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
        self.tcp_option.data = nullptr;
        self.tcp_option_count = 0;
        self.tcp_option_first = offset;
        while (offset < limit) {
            if (!read_ip_payload_tcp_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.tcp_option.size == 0) { self.size = offset; return false; }
            offset += self.tcp_option.size;
            ++self.tcp_option_count;
        }
        self.size = limit;
        return true;
    }

    // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
    bool read_ip_payload_tcp_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's kind, from the IANA TCP Option Kind Numbers registry
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Branch
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) != UINT64_C(0)) && (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) != UINT64_C(1))) {
            if (!read_ip_payload_tcp_option_body(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.tcp_option_body.size;
        } else {
            self.tcp_option_body.data = nullptr;
        }
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ip_payload_tcp_option_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.maximum_segment_size_option.data = nullptr;
        self.window_scale_option.data = nullptr;
        self.sack_permitted_option.data = nullptr;
        self.sack_option.data = nullptr;
        self.timestamps_option.data = nullptr;
        self.tcp_other_option.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(2))) {
            if (!read_ip_payload_maximum_segment_size_option(at, limit)) { return false; }
            self.size = self.maximum_segment_size_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(3))) {
            if (!read_ip_payload_window_scale_option(at, limit)) { return false; }
            self.size = self.window_scale_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(4))) {
            if (!read_ip_payload_sack_permitted_option(at, limit)) { return false; }
            self.size = self.sack_permitted_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(5))) {
            if (!read_ip_payload_sack_option(at, limit)) { return false; }
            self.size = self.sack_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(8))) {
            if (!read_ip_payload_timestamps_option(at, limit)) { return false; }
            self.size = self.timestamps_option.size;
            return true;
        }
        {
            if (!read_ip_payload_tcp_other_option(at, limit)) { return false; }
            self.size = self.tcp_other_option.size;
            return true;
        }
    }

    // Maximum Segment Size option, sent only with Syn
    bool read_ip_payload_maximum_segment_size_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.maximum_segment_size_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The maximum receive segment size at the Tcp endpoint that sends this segment
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // Window Scale option, sent only with Syn
    bool read_ip_payload_window_scale_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.window_scale_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Window scale exponent: the sender's receive window is its Window Size shifted left by this many bits, 0 to 14
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // SACK-Permitted option: selective acknowledgment may be used once the connection is established, sent only with Syn
    bool read_ip_payload_sack_permitted_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_permitted_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // SACK option: the non-contiguous blocks of data received and queued; its length is 8 * n + 2 for n blocks
    bool read_ip_payload_sack_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // One contiguous block of data received and queued
        {
            const std::int64_t budget = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option.tcp_option_length()) - INT64_C(2);
            if (budget < 0 || static_cast<std::size_t>(budget) > limit - offset) { self.size = offset; return false; }
            const std::size_t end = offset + static_cast<std::size_t>(budget);
            self.sack_block.data = nullptr;
            self.sack_block_count = 0;
            self.sack_block_first = offset;
            while (offset < end) {
                if (!read_ip_payload_sack_block(at + offset, end - offset)) { self.size = offset; return false; }
                if (self.sack_block.size == 0) { self.size = offset; return false; }
                offset += self.sack_block.size;
                ++self.sack_block_count;
            }
        }
        self.size = offset;
        return true;
    }

    // One contiguous block of data received and queued
    bool read_ip_payload_sack_block(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option.sack_block;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The first sequence number of the block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The sequence number immediately following the last sequence number of the block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // Timestamps option
    bool read_ip_payload_timestamps_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.timestamps_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // TSval: the current value of the sender's timestamp clock
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // TSecr: the TSval most recently received from the remote Tcp, when Ack is set
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // An option this model gives no layout: its length, then its data
    bool read_ip_payload_tcp_other_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.tcp_other_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The option's data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.tcp_other_option.tcp_option_length()) - INT64_C(2);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.tcp_option_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // User Datagram Protocol datagram: its ports, then what it carries
    bool read_ip_payload_udp_datagram(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.udp_datagram;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Port of the sending process, when meaningful; zero when not used
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Port the datagram is sent to; a market data feed's channel
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the datagram, this header and the data: at least 8
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.udp_datagram.udp_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // 16 bit one's complement of the one's complement sum of a pseudo header, the Udp header and the data, padded with zero octets to a multiple of two. Over IPv4 the pseudo header is the source address, destination address, zero, protocol and Udp length (RFC 768); over IPv6 it is the source and destination address, a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1). A computed checksum of zero is transmitted as all ones (RFC 768). All zero when the sender generated no checksum, which IPv4 allows; over IPv6 the checksum is not optional, and a receiver discards a datagram whose checksum is zero (RFC 8200 8.1)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The datagram's data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.udp_datagram.udp_length()) - INT64_C(8);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.udp_payload_size = bytes;
            offset += bytes;
        }
        self.size = limit;
        return true;
    }

    // Internet Control Message Protocol message: its type, code and checksum, then the body its type gives
    bool read_icmp_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The type of the message, from the IANA ICMP Type Numbers registry
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Further qualifies the type; each message's description lists the codes RFC 792 gives it
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The 16 bit one's complement of the one's complement sum of the ICMP message starting with the ICMP Type, computed with this field zero; an odd length message is padded with one zero octet for the computation
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Branch
        if (!read_icmp_body(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.icmp_body.size;
        self.size = offset;
        return true;
    }

    // Branch
    bool read_icmp_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.icmp_echo_message.data = nullptr;
        self.icmp_destination_unreachable_message.data = nullptr;
        self.icmp_source_quench_message.data = nullptr;
        self.icmp_redirect_message.data = nullptr;
        self.icmp_time_exceeded_message.data = nullptr;
        self.icmp_parameter_problem_message.data = nullptr;
        self.icmp_timestamp_message.data = nullptr;
        self.icmp_information_message.data = nullptr;
        self.icmp_other_message.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(0)) || (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(8))) {
            if (!read_icmp_echo_message(at, limit)) { return false; }
            self.size = self.icmp_echo_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(3))) {
            if (!read_icmp_destination_unreachable_message(at, limit)) { return false; }
            self.size = self.icmp_destination_unreachable_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(4))) {
            if (!read_icmp_source_quench_message(at, limit)) { return false; }
            self.size = self.icmp_source_quench_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(5))) {
            if (!read_icmp_redirect_message(at, limit)) { return false; }
            self.size = self.icmp_redirect_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(11))) {
            if (!read_icmp_time_exceeded_message(at, limit)) { return false; }
            self.size = self.icmp_time_exceeded_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(12))) {
            if (!read_icmp_parameter_problem_message(at, limit)) { return false; }
            self.size = self.icmp_parameter_problem_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(13)) || (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(14))) {
            if (!read_icmp_timestamp_message(at, limit)) { return false; }
            self.size = self.icmp_timestamp_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(15)) || (this->ethernet_frame.ethernet_payload.ip_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_type()) == UINT64_C(16))) {
            if (!read_icmp_information_message(at, limit)) { return false; }
            self.size = self.icmp_information_message.size;
            return true;
        }
        {
            if (!read_icmp_other_message(at, limit)) { return false; }
            self.size = self.icmp_other_message.size;
            return true;
        }
    }

    // Echo or Echo Reply message: code 0; the data received in the echo message must be returned in the echo reply
    bool read_icmp_echo_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_echo_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // An identifier to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // A sequence number to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Data sent in the echo, returned in the reply
        self.icmp_echo_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Destination Unreachable message; codes 0 net unreachable, 1 host unreachable, 2 protocol unreachable, 3 port unreachable, 4 fragmentation needed and DF set, 5 source route failed
    bool read_icmp_destination_unreachable_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_destination_unreachable_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Unused: zero
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The size in octets of the largest datagram that could be forwarded, along the path of the original datagram, without being fragmented at this router: IP header and data, no lower-level headers (RFC 1191 4). Meaningful for code 4 (fragmentation needed and DF set); zero from a router that does not implement RFC 1191
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
        self.icmp_original_datagram_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Source Quench message (deprecated by RFC 6633); code 0
    bool read_icmp_source_quench_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_source_quench_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Unused: zero
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
        self.icmp_original_datagram_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Redirect message; codes 0 redirect datagrams for the network, 1 for the host, 2 for the type of service and network, 3 for the type of service and host
    bool read_icmp_redirect_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_redirect_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Address of the gateway to which traffic for the network specified in the internet destination network field of the original datagram's data should be sent
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
        self.icmp_original_datagram_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Time Exceeded message; codes 0 time to live exceeded in transit, 1 fragment reassembly time exceeded
    bool read_icmp_time_exceeded_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_time_exceeded_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Unused: zero
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Unused: zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
        self.icmp_original_datagram_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Parameter Problem message; code 0 pointer indicates the error
    bool read_icmp_parameter_problem_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_parameter_problem_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // If code is 0, identifies the octet of the original datagram's header where an error was detected
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Length of the padded original datagram field, in 32 bit words (RFC 4884 4.1-4.3); zero when the message carries no extensions (RFC 4884 5.4)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Unused: zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The internet header plus the first 64 bits of the original datagram's data, which the host uses to match the message to the process; a higher level protocol's ports are assumed to be in those 64 bits
        self.icmp_original_datagram_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Timestamp or Timestamp Reply message: code 0; each timestamp is 32 bits of milliseconds since midnight UT, or any time with its high order bit set when the time is not available in milliseconds or cannot be given with respect to midnight UT
    bool read_icmp_timestamp_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_timestamp_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // An identifier to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // A sequence number to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The time the sender last touched the message before sending it, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The time the echoer first touched it on receipt, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The time the echoer last touched the message on sending it, in milliseconds since midnight UT; when the time is not available in milliseconds or cannot be given with respect to midnight UT, any time with the high order bit set to show the value is non-standard
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // Information Request or Information Reply message (deprecated by RFC 6918): code 0
    bool read_icmp_information_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_information_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // An identifier to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // A sequence number to aid in matching requests and replies; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // A message this model gives no layout: the rest of the message
    bool read_icmp_other_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.icmp_message.icmp_body.icmp_other_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The message's body after the checksum
        self.icmp_message_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // A payload this model gives no layout: any other protocol, or a fragment past the first
    bool read_ip_other_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ip_packet.ip_payload.ip_other_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The payload's octets
        self.ip_other_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Internet Protocol version 6 packet: its header and extension headers, then what it carries
    bool read_ipv6_packet(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The version, the traffic class and the flow label, most significant bit first
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Length of the IPv6 payload, the rest of the packet following this header, in octets; extension headers present are part of the payload. Zero in every packet that carries the Jumbo Payload option (RFC 2675 3)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload_length()) + INT64_C(40);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Decremented by 1 by each node that forwards the packet; the packet is discarded when it reaches zero in forwarding
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // 128 bit address of the originator of the packet (RFC 4291)
        if (offset + 16 > limit) { self.size = offset; return false; }
        offset += 16;
        // 128 bit address of the intended recipient of the packet; not the ultimate recipient when a Routing header is present
        if (offset + 16 > limit) { self.size = offset; return false; }
        offset += 16;
        // Branch
        self.ipv6_extension_header.data = nullptr;
        self.ipv6_extension_header_count = 0;
        self.ipv6_extension_header_first = offset;
        while (((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(0)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) || ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(43)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) || ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(44)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) || ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(51)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) || ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(60)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0)))) {
            if (!read_ipv6_extension_header(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.ipv6_extension_header.size == 0) { self.size = offset; return false; }
            offset += self.ipv6_extension_header.size;
            ++self.ipv6_extension_header_count;
        }
        // Branch
        if (!read_ipv6_payload(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.ipv6_payload.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_ipv6_extension_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.hop_by_hop_options_header.data = nullptr;
        self.routing_header.data = nullptr;
        self.fragment_header.data = nullptr;
        self.authentication_header.data = nullptr;
        self.destination_options_header.data = nullptr;
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(0))) {
            if (!read_hop_by_hop_options_header(at, limit)) { return false; }
            self.size = self.hop_by_hop_options_header.size;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(43))) {
            if (!read_routing_header(at, limit)) { return false; }
            self.size = self.routing_header.size;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(44))) {
            if (!read_fragment_header(at, limit)) { return false; }
            self.size = self.fragment_header.size;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(51))) {
            if (!read_authentication_header(at, limit)) { return false; }
            self.size = self.authentication_header.size;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(60))) {
            if (!read_destination_options_header(at, limit)) { return false; }
            self.size = self.destination_options_header.size;
            return true;
        }
        return false;
    }

    // Hop-by-Hop Options header: options every node along the delivery path may examine (RFC 8200 4.3)
    bool read_hop_by_hop_options_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Length of the Hop-by-Hop Options header in 8 octet units, not including the first 8 octets
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The header's TLV encoded options, to the header's end
        // stepped over at its size; its entries are read on asking (read_hop_by_hop_options_ipv6_option)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_hdr_ext_len()) * INT64_C(8) + INT64_C(6);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.hop_by_hop_options.data = at + offset;
            self.hop_by_hop_options.size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The header's TLV encoded options, to the header's end
    bool read_hop_by_hop_options(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_hdr_ext_len()) * INT64_C(8) + INT64_C(6);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // One option: its type, then its data length and data for every type but Pad1
        self.ipv6_option.data = nullptr;
        self.ipv6_option_count = 0;
        self.ipv6_option_first = offset;
        while (offset < limit) {
            if (!read_hop_by_hop_options_ipv6_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.ipv6_option.size == 0) { self.size = offset; return false; }
            offset += self.ipv6_option.size;
            ++self.ipv6_option_count;
        }
        self.size = limit;
        return true;
    }

    // One option: its type, then its data length and data for every type but Pad1
    bool read_hop_by_hop_options_ipv6_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options.ipv6_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's full 8 bit type: the high 2 bits say what a node that does not recognize it must do, the third whether its data may change en route (IANA Destination Options and Hop-by-Hop Options)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // An option's data length and its data
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options.ipv6_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options.ipv6_option.ipv6_option_type()) != UINT64_C(0))) {
            if (!read_hop_by_hop_options_ipv6_tlv_option(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.ipv6_tlv_option.size;
        } else {
            self.ipv6_tlv_option.data = nullptr;
        }
        self.size = offset;
        return true;
    }

    // An option's data length and its data
    bool read_hop_by_hop_options_ipv6_tlv_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options.ipv6_option.ipv6_tlv_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Length of the Option Data field of this option, in octets
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Option type specific data; for PadN, zero octets
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.hop_by_hop_options_header.hop_by_hop_options.ipv6_option.ipv6_tlv_option.opt_data_len());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.ipv6_option_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Routing header: intermediate nodes to be visited on the way to the packet's destination (RFC 8200 4.4)
    bool read_routing_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.routing_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Length of the Routing header in 8 octet units, not including the first 8 octets
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Identifier of a particular Routing header variant
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Number of explicitly listed intermediate nodes still to be visited before reaching the final destination
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Data of the format the Routing Type determines, of length such that the header is a multiple of 8 octets
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.routing_header.routing_hdr_ext_len()) * INT64_C(8) + INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.routing_type_specific_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Fragment header: one fragment of a packet the source divided to fit the path MTU (RFC 8200 4.5); its Next Header names the initial header type of the Fragmentable Part of the original packet
    bool read_fragment_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.fragment_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Reserved: initialized to zero for transmission, ignored on reception
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The fragment offset, two reserved bits and the M flag, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        stored_ipv6_fragment_offset = static_cast<std::uint64_t>(self.ipv6_fragment_offset());
        has_stored_ipv6_fragment_offset = true;
        offset += 2;
        // Identifies the fragments of one original packet: different from that of any other fragmented packet sent recently with the same source and destination addresses
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // IP Authentication Header: integrity and data origin authentication for the packet (RFC 4302 2); its length is measured in 32 bit words, not the 64 bit words of the other extension headers
    bool read_authentication_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.authentication_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Length of the Authentication Header in 32 bit words (4 octet units), minus 2 (RFC 4302 2.2)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Reserved for future use: set to zero by the sender, ignored by the recipient (RFC 4302 2.3)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // SPI: an arbitrary 32 bit value a receiver uses to identify the security association to which an incoming packet is bound (RFC 4302 2.4)
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // An unsigned 32 bit counter, the low-order 32 bits of the packet's sequence number, increasing by one for each packet sent on the security association (RFC 4302 2.5)
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The Integrity Check Value for this packet, with any padding that makes the header a multiple of 8 octets over IPv6 (RFC 4302 2.6)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.authentication_header.ah_payload_length()) * INT64_C(4) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.integrity_check_value_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Destination Options header: options examined only by the packet's destination node(s) (RFC 8200 4.6)
    bool read_destination_options_header(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the type of header immediately following this header (the IPv6 header or an extension header), with the same values as the IPv4 Protocol field
        if (offset + 1 > limit) { self.size = offset; return false; }
        stored_ipv6_next_header = static_cast<std::uint64_t>(self.ipv6_next_header());
        has_stored_ipv6_next_header = true;
        offset += 1;
        // Length of the Destination Options header in 8 octet units, not including the first 8 octets
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The header's TLV encoded options, to the header's end
        // stepped over at its size; its entries are read on asking (read_destination_options_ipv6_option)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options_hdr_ext_len()) * INT64_C(8) + INT64_C(6);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.destination_options.data = at + offset;
            self.destination_options.size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The header's TLV encoded options, to the header's end
    bool read_destination_options(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options_hdr_ext_len()) * INT64_C(8) + INT64_C(6);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // One option: its type, then its data length and data for every type but Pad1
        self.ipv6_option.data = nullptr;
        self.ipv6_option_count = 0;
        self.ipv6_option_first = offset;
        while (offset < limit) {
            if (!read_destination_options_ipv6_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.ipv6_option.size == 0) { self.size = offset; return false; }
            offset += self.ipv6_option.size;
            ++self.ipv6_option_count;
        }
        self.size = limit;
        return true;
    }

    // One option: its type, then its data length and data for every type but Pad1
    bool read_destination_options_ipv6_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options.ipv6_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's full 8 bit type: the high 2 bits say what a node that does not recognize it must do, the third whether its data may change en route (IANA Destination Options and Hop-by-Hop Options)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // An option's data length and its data
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options.ipv6_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options.ipv6_option.ipv6_option_type()) != UINT64_C(0))) {
            if (!read_destination_options_ipv6_tlv_option(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.ipv6_tlv_option.size;
        } else {
            self.ipv6_tlv_option.data = nullptr;
        }
        self.size = offset;
        return true;
    }

    // An option's data length and its data
    bool read_destination_options_ipv6_tlv_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options.ipv6_option.ipv6_tlv_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Length of the Option Data field of this option, in octets
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Option type specific data; for PadN, zero octets
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_extension_header.destination_options_header.destination_options.ipv6_option.ipv6_tlv_option.opt_data_len());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.ipv6_option_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ipv6_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.tcp_segment.data = nullptr;
        self.udp_datagram.data = nullptr;
        self.icmpv6_message.data = nullptr;
        self.ipv6_other_payload.data = nullptr;
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(6)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) {
            if (!read_ipv6_payload_tcp_segment(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(17)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) {
            if (!read_ipv6_payload_udp_datagram(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        if ((has_stored_ipv6_next_header && stored_ipv6_next_header == UINT64_C(58)) && (!has_stored_ipv6_fragment_offset || stored_ipv6_fragment_offset == UINT64_C(0))) {
            if (!read_icmpv6_message(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
        {
            if (!read_ipv6_other_payload(at, limit)) { return false; }
            self.size = limit;
            return true;
        }
    }

    // Transmission Control Protocol segment: its ports and stream position, then a piece of the stream
    bool read_ipv6_payload_tcp_segment(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Port the segment is sent from
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Port the segment is sent to
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The sequence number of the first data octet in this segment; when Syn is set, the initial sequence number
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // When Ack is set, the next sequence number the sender of the segment expects to receive
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The header length and the control flags, most significant bit first
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets, beginning with the one the acknowledgment field indicates, the sender is willing to accept; shifted by the Window Scale option's shift count when scaling is in use
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Ones' complement of the ones' complement sum of the pseudo header, the Tcp header with its options, and the data, padded to 16 bits; computed with this field zero. Over IPv4 the pseudo header is the source and destination address, zero, protocol and Tcp length (RFC 9293 3.1); over IPv6 it is the source and destination address (the final destination when a Routing header is present), a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Offset from the segment's sequence number to the octet following the urgent data; only interpreted when Urg is set
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Tcp options, and any padding after the End of Option List
        // stepped over at its size; its entries are read on asking (read_ipv6_payload_tcp_option)
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data_offset()) * INT64_C(4) - INT64_C(20);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.tcp_options.data = at + offset;
            self.tcp_options.size = bytes;
            offset += bytes;
        }
        // The segment's data: a piece of the byte stream
        self.tcp_payload_at = offset; self.tcp_payload_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Tcp options, and any padding after the End of Option List
    bool read_ipv6_payload_tcp_options(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data_offset()) * INT64_C(4) - INT64_C(20);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
        self.tcp_option.data = nullptr;
        self.tcp_option_count = 0;
        self.tcp_option_first = offset;
        while (offset < limit) {
            if (!read_ipv6_payload_tcp_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.tcp_option.size == 0) { self.size = offset; return false; }
            offset += self.tcp_option.size;
            ++self.tcp_option_count;
        }
        self.size = limit;
        return true;
    }

    // One option: its kind, then its length and data for every kind but End of Option List and No-Operation
    bool read_ipv6_payload_tcp_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's kind, from the IANA TCP Option Kind Numbers registry
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Branch
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) != UINT64_C(0)) && (this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) != UINT64_C(1))) {
            if (!read_ipv6_payload_tcp_option_body(at + offset, limit - offset)) { self.size = offset; return false; }
            offset += self.tcp_option_body.size;
        } else {
            self.tcp_option_body.data = nullptr;
        }
        self.size = offset;
        return true;
    }

    // Branch
    bool read_ipv6_payload_tcp_option_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.maximum_segment_size_option.data = nullptr;
        self.window_scale_option.data = nullptr;
        self.sack_permitted_option.data = nullptr;
        self.sack_option.data = nullptr;
        self.timestamps_option.data = nullptr;
        self.tcp_other_option.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(2))) {
            if (!read_ipv6_payload_maximum_segment_size_option(at, limit)) { return false; }
            self.size = self.maximum_segment_size_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(3))) {
            if (!read_ipv6_payload_window_scale_option(at, limit)) { return false; }
            self.size = self.window_scale_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(4))) {
            if (!read_ipv6_payload_sack_permitted_option(at, limit)) { return false; }
            self.size = self.sack_permitted_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(5))) {
            if (!read_ipv6_payload_sack_option(at, limit)) { return false; }
            self.size = self.sack_option.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_kind()) == UINT64_C(8))) {
            if (!read_ipv6_payload_timestamps_option(at, limit)) { return false; }
            self.size = self.timestamps_option.size;
            return true;
        }
        {
            if (!read_ipv6_payload_tcp_other_option(at, limit)) { return false; }
            self.size = self.tcp_other_option.size;
            return true;
        }
    }

    // Maximum Segment Size option, sent only with Syn
    bool read_ipv6_payload_maximum_segment_size_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.maximum_segment_size_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The maximum receive segment size at the Tcp endpoint that sends this segment
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        self.size = offset;
        return true;
    }

    // Window Scale option, sent only with Syn
    bool read_ipv6_payload_window_scale_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.window_scale_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Window scale exponent: the sender's receive window is its Window Size shifted left by this many bits, 0 to 14
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // SACK-Permitted option: selective acknowledgment may be used once the connection is established, sent only with Syn
    bool read_ipv6_payload_sack_permitted_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_permitted_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // SACK option: the non-contiguous blocks of data received and queued; its length is 8 * n + 2 for n blocks
    bool read_ipv6_payload_sack_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // One contiguous block of data received and queued
        {
            const std::int64_t budget = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option.tcp_option_length()) - INT64_C(2);
            if (budget < 0 || static_cast<std::size_t>(budget) > limit - offset) { self.size = offset; return false; }
            const std::size_t end = offset + static_cast<std::size_t>(budget);
            self.sack_block.data = nullptr;
            self.sack_block_count = 0;
            self.sack_block_first = offset;
            while (offset < end) {
                if (!read_ipv6_payload_sack_block(at + offset, end - offset)) { self.size = offset; return false; }
                if (self.sack_block.size == 0) { self.size = offset; return false; }
                offset += self.sack_block.size;
                ++self.sack_block_count;
            }
        }
        self.size = offset;
        return true;
    }

    // One contiguous block of data received and queued
    bool read_ipv6_payload_sack_block(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.sack_option.sack_block;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The first sequence number of the block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The sequence number immediately following the last sequence number of the block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // Timestamps option
    bool read_ipv6_payload_timestamps_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.timestamps_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // TSval: the current value of the sender's timestamp clock
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // TSecr: the TSval most recently received from the remote Tcp, when Ack is set
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // An option this model gives no layout: its length, then its data
    bool read_ipv6_payload_tcp_other_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.tcp_other_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the option: its kind, this length and its data
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The option's data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.tcp_segment.tcp_options.tcp_option.tcp_option_body.tcp_other_option.tcp_option_length()) - INT64_C(2);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.tcp_option_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // User Datagram Protocol datagram: its ports, then what it carries
    bool read_ipv6_payload_udp_datagram(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.udp_datagram;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Port of the sending process, when meaningful; zero when not used
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Port the datagram is sent to; a market data feed's channel
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the datagram, this header and the data: at least 8
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.udp_datagram.udp_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // 16 bit one's complement of the one's complement sum of a pseudo header, the Udp header and the data, padded with zero octets to a multiple of two. Over IPv4 the pseudo header is the source address, destination address, zero, protocol and Udp length (RFC 768); over IPv6 it is the source and destination address, a 32 bit upper-layer packet length, three zero octets and the next header (RFC 8200 8.1). A computed checksum of zero is transmitted as all ones (RFC 768). All zero when the sender generated no checksum, which IPv4 allows; over IPv6 the checksum is not optional, and a receiver discards a datagram whose checksum is zero (RFC 8200 8.1)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The datagram's data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.udp_datagram.udp_length()) - INT64_C(8);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.udp_payload_size = bytes;
            offset += bytes;
        }
        self.size = limit;
        return true;
    }

    // Internet Control Message Protocol for IPv6 message: its type, code and checksum, then the body its type gives
    bool read_icmpv6_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The type of the message, from the IANA ICMPv6 type registry: 0 to 127 error messages, 128 to 255 informational messages
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Depends on the message type: an additional level of message granularity; each message's description lists the codes RFC 4443 gives it
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The 16 bit one's complement of the one's complement sum of the entire ICMPv6 message, starting with the type field, prepended with the IPv6 pseudo header (source and destination address, upper layer packet length, zero, next header 58), computed with this field zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Branch
        if (!read_icmpv6_body(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.icmpv6_body.size;
        self.size = offset;
        return true;
    }

    // Branch
    bool read_icmpv6_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.icmpv6_destination_unreachable_message.data = nullptr;
        self.icmpv6_packet_too_big_message.data = nullptr;
        self.icmpv6_time_exceeded_message.data = nullptr;
        self.icmpv6_parameter_problem_message.data = nullptr;
        self.icmpv6_echo_message.data = nullptr;
        self.icmpv6_other_message.data = nullptr;
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(1))) {
            if (!read_icmpv6_destination_unreachable_message(at, limit)) { return false; }
            self.size = self.icmpv6_destination_unreachable_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(2))) {
            if (!read_icmpv6_packet_too_big_message(at, limit)) { return false; }
            self.size = self.icmpv6_packet_too_big_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(3))) {
            if (!read_icmpv6_time_exceeded_message(at, limit)) { return false; }
            self.size = self.icmpv6_time_exceeded_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(4))) {
            if (!read_icmpv6_parameter_problem_message(at, limit)) { return false; }
            self.size = self.icmpv6_parameter_problem_message.size;
            return true;
        }
        if ((this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(128)) || (this->ethernet_frame.ethernet_payload.ipv6_packet.data != nullptr && this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.data != nullptr && static_cast<std::uint64_t>(this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_type()) == UINT64_C(129))) {
            if (!read_icmpv6_echo_message(at, limit)) { return false; }
            self.size = self.icmpv6_echo_message.size;
            return true;
        }
        {
            if (!read_icmpv6_other_message(at, limit)) { return false; }
            self.size = self.icmpv6_other_message.size;
            return true;
        }
    }

    // Destination Unreachable message; codes 0 no route to destination, 1 communication with destination administratively prohibited, 2 beyond scope of source address, 3 address unreachable, 4 port unreachable, 5 source address failed ingress/egress policy, 6 reject route to destination
    bool read_icmpv6_destination_unreachable_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_destination_unreachable_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Length of the padded original datagram field, in 64 bit words (RFC 4884 4.4, 4.5); zero when the message carries no extensions (RFC 4884 5.4)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Unused: zero when sent, ignored by the receiver
        if (offset + 3 > limit) { self.size = offset; return false; }
        offset += 3;
        // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
        self.icmpv6_invoking_packet_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Packet Too Big message; code set to 0 by the originator and ignored by the receiver
    bool read_icmpv6_packet_too_big_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_packet_too_big_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The Maximum Transmission Unit of the next-hop link
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
        self.icmpv6_invoking_packet_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Time Exceeded message; codes 0 hop limit exceeded in transit, 1 fragment reassembly time exceeded
    bool read_icmpv6_time_exceeded_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_time_exceeded_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Length of the padded original datagram field, in 64 bit words (RFC 4884 4.4, 4.5); zero when the message carries no extensions (RFC 4884 5.4)
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // Unused: zero when sent, ignored by the receiver
        if (offset + 3 > limit) { self.size = offset; return false; }
        offset += 3;
        // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
        self.icmpv6_invoking_packet_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Parameter Problem message; codes 0 erroneous header field encountered, 1 unrecognized Next Header type encountered, 2 unrecognized IPv6 option encountered
    bool read_icmpv6_parameter_problem_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_parameter_problem_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The octet offset within the invoking packet where the error was detected; beyond the end of the ICMPv6 packet when the field in error does not fit in an ICMPv6 error message
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // As much of the invoking packet as possible without the ICMPv6 packet exceeding the minimum IPv6 MTU
        self.icmpv6_invoking_packet_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Echo Request or Echo Reply message: code 0; the reply's identifier, sequence number and data are those of the request
    bool read_icmpv6_echo_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_echo_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // An identifier to aid in matching Echo Replies to this Echo Request; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // A sequence number to aid in matching Echo Replies to this Echo Request; may be zero
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Zero or more octets of arbitrary data; a reply carries the request's data
        self.icmpv6_echo_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // A message this model gives no layout: the rest of the message
    bool read_icmpv6_other_message(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.icmpv6_message.icmpv6_body.icmpv6_other_message;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The message's body after the checksum
        self.icmpv6_message_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // A payload this model gives no layout: any other next header (59 no next header, 50 Encapsulating Security Payload), or a fragment past the first
    bool read_ipv6_other_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ipv6_packet.ipv6_payload.ipv6_other_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The payload's octets
        self.ipv6_other_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // A payload this model gives no layout: any other Ether Type (Arp, Lldp, ...)
    bool read_ethernet_other_payload(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->ethernet_frame.ethernet_payload.ethernet_other_payload;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The payload's octets
        self.ethernet_other_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }
};

}
