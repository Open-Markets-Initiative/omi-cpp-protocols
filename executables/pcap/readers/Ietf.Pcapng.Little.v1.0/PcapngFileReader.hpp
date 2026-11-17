// Asx.AsxDerivatives.Ntp.Itch.v1.05: pcap/readers/Ietf.Pcapng.Little.v1.0/PcapngFileReader.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace ietf::pcapng::little::v1_0 {

// Pcapng File reader: each part read where the model's rules place it, without copying.
// A struct's data is where it lies, null where it is not there; size is how many bytes it holds,
// or, where reading it failed, how many it got through. Each read function can be called on its own,
// reading with what was read before it.
struct PcapngFileReader {

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

    // Pcapng capture file: blocks, to the end of the file
    struct PcapngFile {
        const std::byte* data = nullptr;
        std::size_t size = 0;

        // General block structure (3.1): type, total length, body, total length again
        struct PcapngBlock {
            const std::byte* data = nullptr;
            std::size_t size = 0;

            // Identifies the block (10.1); values with the most significant bit set are reserved for local use
            [[nodiscard]] std::uint32_t pcapng_block_type() const noexcept { return little<std::uint32_t>(data + 0); }

            // Total size of the block in octets, a multiple of 4: 12 for a block with no body
            [[nodiscard]] std::uint32_t pcapng_block_total_length() const noexcept { return little<std::uint32_t>(data + 4); }

            // The block's body: what its type says, padded to 32 bits
            struct PcapngBlockBody {
                const std::byte* data = nullptr;
                std::size_t size = 0;

                // Branch
                struct PcapngBlockContent {
                    const std::byte* data = nullptr;
                    std::size_t size = 0;

                    // Section Header Block: byte order, version and length of the section, then its options
                    struct PcapngSectionHeaderBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // 1A2B3C4D in the byte order of the section: tells a little endian section from a big endian one
                        [[nodiscard]] std::uint32_t pcapng_byte_order_magic() const noexcept { return little<std::uint32_t>(data + 0); }

                        // Major version of the format: 1
                        [[nodiscard]] std::uint16_t pcapng_major_version() const noexcept { return little<std::uint16_t>(data + 4); }

                        // Minor version of the format: 0 (a reader treats 2 as 0)
                        [[nodiscard]] std::uint16_t pcapng_minor_version() const noexcept { return little<std::uint16_t>(data + 6); }

                        // Octets of the section after this Section Header Block, a multiple of 4; -1 when not specified
                        [[nodiscard]] std::int64_t pcapng_section_length() const noexcept { return static_cast<std::int64_t>(little<std::uint64_t>(data + 8)); }

                        // One Section Header Block option: its code, length and value
                        struct PcapngShbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Section Header Block's own
                            [[nodiscard]] std::uint16_t pcapng_shb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngShbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngShbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;

                                    // Description of the hardware used to create this section
                                    struct PcapngShbHardwareOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Description of the hardware used to create this section, UTF-8, not zero terminated
                                        std::size_t pcapng_shb_hardware_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_shb_hardware() const noexcept { return data + 0; }
                                    };
                                    PcapngShbHardwareOption pcapng_shb_hardware_option;

                                    // Name of the operating system used to create this section
                                    struct PcapngShbOsOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Name of the operating system used to create this section, UTF-8, not zero terminated
                                        std::size_t pcapng_shb_os_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_shb_os() const noexcept { return data + 0; }
                                    };
                                    PcapngShbOsOption pcapng_shb_os_option;

                                    // Name of the application used to create this section
                                    struct PcapngShbUserApplicationOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Name of the application used to create this section, UTF-8, not zero terminated
                                        std::size_t pcapng_shb_user_application_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_shb_user_application() const noexcept { return data + 0; }
                                    };
                                    PcapngShbUserApplicationOption pcapng_shb_user_application_option;
                                };
                                PcapngShbOptionContent pcapng_shb_option_content;
                            };
                            PcapngShbOptionValue pcapng_shb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngShbOption pcapng_shb_option;
                        std::size_t pcapng_shb_option_count = 0;   // entries read
                        std::size_t pcapng_shb_option_first = 0;   // where the first lies
                    };
                    PcapngSectionHeaderBody pcapng_section_header_body;

                    // Interface Description Block: an interface's link layer and snapshot length, then its options; interfaces are numbered from 0 in the order of their blocks within a section
                    struct PcapngInterfaceDescriptionBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Link layer type of the interface, from the PCAP-related LinkType registry (draft-ietf-opsawg-pcaplinktype)
                        [[nodiscard]] std::uint16_t pcapng_link_type() const noexcept { return little<std::uint16_t>(data + 0); }

                        // Not used: zero, ignored by readers
                        static constexpr std::size_t pcapng_idb_reserved_size = 2;
                        [[nodiscard]] const std::byte* pcapng_idb_reserved() const noexcept { return data + 2; }

                        // Most octets captured from each packet; 0 for no limit
                        [[nodiscard]] std::uint32_t pcapng_snap_len() const noexcept { return little<std::uint32_t>(data + 4); }

                        // One Interface Description Block option: its code, length and value
                        struct PcapngIdbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Interface Description Block's own
                            [[nodiscard]] std::uint16_t pcapng_idb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngIdbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngIdbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;

                                    // Name of the device used to capture data
                                    struct PcapngIfNameOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Name of the device used to capture data, UTF-8, not zero terminated
                                        std::size_t pcapng_if_name_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_name() const noexcept { return data + 0; }
                                    };
                                    PcapngIfNameOption pcapng_if_name_option;

                                    // Description of the device used to capture data
                                    struct PcapngIfDescriptionOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Description of the device used to capture data, UTF-8, not zero terminated
                                        std::size_t pcapng_if_description_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_description() const noexcept { return data + 0; }
                                    };
                                    PcapngIfDescriptionOption pcapng_if_description_option;

                                    // if_IPv4addr: an IPv4 address and netmask, four octets each, not affected by the section's byte order
                                    struct PcapngIfIpv4AddressOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IPv4 address of the interface, in network order
                                        static constexpr std::size_t pcapng_if_ipv4_address_size = 4;
                                        [[nodiscard]] const std::byte* pcapng_if_ipv4_address() const noexcept { return data + 0; }

                                        // Netmask of the address, in network order
                                        static constexpr std::size_t pcapng_if_ipv4_netmask_size = 4;
                                        [[nodiscard]] const std::byte* pcapng_if_ipv4_netmask() const noexcept { return data + 4; }
                                    };
                                    PcapngIfIpv4AddressOption pcapng_if_ipv4_address_option;

                                    // if_IPv6addr: an IPv6 address and its prefix length
                                    struct PcapngIfIpv6AddressOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IPv6 address of the interface, 16 octets in network order
                                        static constexpr std::size_t pcapng_if_ipv6_address_size = 16;
                                        [[nodiscard]] const std::byte* pcapng_if_ipv6_address() const noexcept { return data + 0; }

                                        // Prefix length of the address, in bits
                                        [[nodiscard]] std::uint8_t pcapng_if_ipv6_prefix_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 16)); }
                                    };
                                    PcapngIfIpv6AddressOption pcapng_if_ipv6_address_option;

                                    // if_MACaddr: the interface hardware EUI-48 address
                                    struct PcapngIfMacAddressOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Interface hardware EUI-48 (MAC) address
                                        static constexpr std::size_t pcapng_if_mac_address_size = 6;
                                        [[nodiscard]] const std::byte* pcapng_if_mac_address() const noexcept { return data + 0; }
                                    };
                                    PcapngIfMacAddressOption pcapng_if_mac_address_option;

                                    // if_EUIaddr: the interface hardware EUI-64 address
                                    struct PcapngIfEuiAddressOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Interface hardware EUI-64 address
                                        static constexpr std::size_t pcapng_if_eui_address_size = 8;
                                        [[nodiscard]] const std::byte* pcapng_if_eui_address() const noexcept { return data + 0; }
                                    };
                                    PcapngIfEuiAddressOption pcapng_if_eui_address_option;

                                    // if_speed: the interface speed
                                    struct PcapngIfSpeedOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Interface speed, bits per second
                                        [[nodiscard]] std::uint64_t pcapng_if_speed() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngIfSpeedOption pcapng_if_speed_option;

                                    // if_tsresol: the resolution of the interface's timestamps; 10^-6 s when absent
                                    struct PcapngIfTimestampResolution {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;
                                        // if_tsresol: the resolution of the interface's timestamps; 10^-6 s when absent
                                        [[nodiscard]] std::uint8_t pcapng_if_timestamp_resolution() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }
                                        // Low 7 bits: the resolution as a negative power of the base, 6 for microseconds
                                        [[nodiscard]] std::uint8_t pcapng_if_timestamp_resolution_exponent() const noexcept { return static_cast<std::uint8_t>((pcapng_if_timestamp_resolution() >> 0) & 0x7Fu); }
                                        // Most significant bit: 0 for a negative power of 10, 1 for a negative power of 2
                                        [[nodiscard]] bool pcapng_if_timestamp_resolution_base() const noexcept { return ((pcapng_if_timestamp_resolution() >> 7) & 1u) != 0; }
                                    };
                                    PcapngIfTimestampResolution pcapng_if_timestamp_resolution;

                                    // if_filter: the filter used to capture traffic
                                    struct PcapngIfFilterOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Code of the filter used, such as a libpcap string or BPF bytecode
                                        [[nodiscard]] std::uint8_t pcapng_if_filter_code() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The filter, as its code says
                                        std::size_t pcapng_if_filter_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_filter() const noexcept { return data + 1; }
                                    };
                                    PcapngIfFilterOption pcapng_if_filter_option;

                                    // Name of the operating system of the machine the interface is installed in
                                    struct PcapngIfOsOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Name of the operating system of the machine the interface is installed in, UTF-8, not zero terminated
                                        std::size_t pcapng_if_os_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_os() const noexcept { return data + 0; }
                                    };
                                    PcapngIfOsOption pcapng_if_os_option;

                                    // if_fcslen: the length of the Frame Check Sequence for this interface
                                    struct PcapngIfFcsLengthOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Length of the Frame Check Sequence, in bits
                                        [[nodiscard]] std::uint8_t pcapng_if_fcs_length() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }
                                    };
                                    PcapngIfFcsLengthOption pcapng_if_fcs_length_option;

                                    // if_tsoffset: an offset added to each packet's timestamp
                                    struct PcapngIfTimestampOffsetOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Seconds added to the timestamp of each packet to obtain its absolute timestamp; 0 when absent
                                        [[nodiscard]] std::int64_t pcapng_if_timestamp_offset() const noexcept { return static_cast<std::int64_t>(little<std::uint64_t>(data + 0)); }
                                    };
                                    PcapngIfTimestampOffsetOption pcapng_if_timestamp_offset_option;

                                    // Description of the interface hardware
                                    struct PcapngIfHardwareOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Description of the interface hardware, UTF-8, not zero terminated
                                        std::size_t pcapng_if_hardware_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_hardware() const noexcept { return data + 0; }
                                    };
                                    PcapngIfHardwareOption pcapng_if_hardware_option;

                                    // if_txspeed: the interface transmit speed
                                    struct PcapngIfTransmitSpeedOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Interface transmit speed, bits per second
                                        [[nodiscard]] std::uint64_t pcapng_if_transmit_speed() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngIfTransmitSpeedOption pcapng_if_transmit_speed_option;

                                    // if_rxspeed: the interface receive speed
                                    struct PcapngIfReceiveSpeedOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Interface receive speed, bits per second
                                        [[nodiscard]] std::uint64_t pcapng_if_receive_speed() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngIfReceiveSpeedOption pcapng_if_receive_speed_option;

                                    // IANA time zone database name of the interface's time zone
                                    struct PcapngIfIanaTimeZoneNameOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA time zone database name of the interface's time zone, UTF-8, not zero terminated
                                        std::size_t pcapng_if_iana_time_zone_name_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_if_iana_time_zone_name() const noexcept { return data + 0; }
                                    };
                                    PcapngIfIanaTimeZoneNameOption pcapng_if_iana_time_zone_name_option;
                                };
                                PcapngIdbOptionContent pcapng_idb_option_content;
                            };
                            PcapngIdbOptionValue pcapng_idb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngIdbOption pcapng_idb_option;
                        std::size_t pcapng_idb_option_count = 0;   // entries read
                        std::size_t pcapng_idb_option_first = 0;   // where the first lies
                    };
                    PcapngInterfaceDescriptionBody pcapng_interface_description_body;

                    // Packet Block: one captured packet, superseded by the Enhanced Packet Block
                    struct PcapngPacketBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The interface the packet comes from, 16 bits
                        [[nodiscard]] std::uint16_t pcapng_packet_interface_id() const noexcept { return little<std::uint16_t>(data + 0); }

                        // A local drop counter: packets lost between this packet and the preceding one; 0xFFFF when not available
                        [[nodiscard]] std::uint16_t pcapng_drops_count() const noexcept { return little<std::uint16_t>(data + 2); }

                        // Upper 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_packet_timestamp_upper() const noexcept { return little<std::uint32_t>(data + 4 + 0); }
                        // Lower 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_packet_timestamp_lower() const noexcept { return little<std::uint32_t>(data + 4 + 4); }
                        // When the packet was captured
                        [[nodiscard]] std::uint64_t pcapng_packet_timestamp() const noexcept { return static_cast<std::uint64_t>(pcapng_packet_timestamp_upper()) * UINT64_C(4294967296) + static_cast<std::uint64_t>(pcapng_packet_timestamp_lower()); }

                        // Octets captured from the packet: the length of Packet Data, without its padding
                        [[nodiscard]] std::uint32_t pcapng_captured_packet_length() const noexcept { return little<std::uint32_t>(data + 12); }

                        // Octets of the packet as it was transmitted on the network
                        [[nodiscard]] std::uint32_t pcapng_original_packet_length() const noexcept { return little<std::uint32_t>(data + 16); }

                        // The packet as captured, link-layer headers first, in the format of the interface's LinkType
                        std::size_t pcapng_packet_data_size = 0;
                        [[nodiscard]] const std::byte* pcapng_packet_data() const noexcept { return data + 20; }

                        std::size_t pcapng_packet_data_padding_at = 0;
                        // Zero octets bringing the packet data to a 32 bit boundary
                        std::size_t pcapng_packet_data_padding_size = 0;
                        [[nodiscard]] const std::byte* pcapng_packet_data_padding() const noexcept { return data + pcapng_packet_data_padding_at; }

                        // One Packet Block option: its code, length and value
                        struct PcapngPbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Packet Block's own
                            [[nodiscard]] std::uint16_t pcapng_pb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngPbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngPbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;

                                    // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
                                    struct PcapngEpbFlags {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;
                                        // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
                                        [[nodiscard]] std::uint32_t pcapng_epb_flags() const noexcept { return little<std::uint32_t>(data + 0); }
                                        // Bits 0-1: inbound / outbound (00 information not available, 01 inbound, 10 outbound)
                                        [[nodiscard]] std::uint8_t pcapng_direction() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 0) & 0x3u); }
                                        // Bits 2-4: 000 not specified, 001 unicast, 010 multicast, 011 broadcast, 100 promiscuous
                                        [[nodiscard]] std::uint8_t pcapng_reception_type() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 2) & 0x7u); }
                                        // Bits 5-8: FCS length in octets, 0 when not available; overrides the interface's if_fcslen
                                        [[nodiscard]] std::uint8_t pcapng_fcs_length() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 5) & 0xFu); }
                                        // Bit 9: checksum not ready, as a consequence of checksum offloading
                                        [[nodiscard]] bool pcapng_checksum_not_ready() const noexcept { return ((pcapng_epb_flags() >> 9) & 1u) != 0; }
                                        // Bit 10: the checksum was already checked on the receive path
                                        [[nodiscard]] bool pcapng_checksum_valid() const noexcept { return ((pcapng_epb_flags() >> 10) & 1u) != 0; }
                                        // Bit 11: TCP segmentation offloaded
                                        [[nodiscard]] bool pcapng_tcp_segmentation_offloaded() const noexcept { return ((pcapng_epb_flags() >> 11) & 1u) != 0; }
                                        // Bits 16-31: link-layer-dependent errors (31 symbol, 30 preamble, 29 start frame delimiter, 28 unaligned frame, 27 wrong inter frame gap, 26 packet too short, 25 packet too long, 24 CRC)
                                        [[nodiscard]] std::uint16_t pcapng_link_layer_errors() const noexcept { return static_cast<std::uint16_t>((pcapng_epb_flags() >> 16) & 0xFFFFu); }
                                    };
                                    PcapngEpbFlags pcapng_epb_flags;

                                    // epb_hash: a hash of the packet, which covers only the packet, not the capture driver's header
                                    struct PcapngEpbHashOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // The hashing algorithm, which gives the hash's size
                                        [[nodiscard]] std::uint8_t pcapng_hash_algorithm() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The hash of the packet
                                        std::size_t pcapng_hash_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_hash() const noexcept { return data + 1; }
                                    };
                                    PcapngEpbHashOption pcapng_epb_hash_option;
                                };
                                PcapngPbOptionContent pcapng_pb_option_content;
                            };
                            PcapngPbOptionValue pcapng_pb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngPbOption pcapng_pb_option;
                        std::size_t pcapng_pb_option_count = 0;   // entries read
                        std::size_t pcapng_pb_option_first = 0;   // where the first lies
                    };
                    PcapngPacketBody pcapng_packet_body;

                    // Simple Packet Block: one packet of interface 0, with only its original length
                    struct PcapngSimplePacketBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // Octets of the packet as it was transmitted on the network
                        [[nodiscard]] std::uint32_t pcapng_original_packet_length() const noexcept { return little<std::uint32_t>(data + 0); }

                        // The packet, link-layer headers first: the rest of the body, the lesser of the interface's SnapLen and the original length followed by padding to 32 bits
                        std::size_t pcapng_simple_packet_data_size = 0;
                        [[nodiscard]] const std::byte* pcapng_simple_packet_data() const noexcept { return data + 4; }
                    };
                    PcapngSimplePacketBody pcapng_simple_packet_body;

                    // Name Resolution Block: name resolution records to nrb_record_end, then options in the same Type - Length - Value form
                    struct PcapngNameResolutionBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // One name resolution record, or after nrb_record_end one option (ns_dnsname 2, ns_dnsIP4addr 3, ns_dnsIP6addr 4, opt_comment 1): type, length, value padded to 32 bits
                        struct PcapngNameRecord {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The record type; after nrb_record_end, an option code
                            [[nodiscard]] std::uint16_t pcapng_record_type() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The record's address followed by one or more zero terminated UTF-8 names (or an option's value); ns_dnsname is a UTF-8 string, ns_dnsIP4addr 4 and ns_dnsIP6addr 16 octets
                            std::size_t pcapng_record_value_size = 0;
                            [[nodiscard]] const std::byte* pcapng_record_value() const noexcept { return data + 4; }

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngNameRecord pcapng_name_record;
                        std::size_t pcapng_name_record_count = 0;   // entries read
                        std::size_t pcapng_name_record_first = 0;   // where the first lies
                    };
                    PcapngNameResolutionBody pcapng_name_resolution_body;

                    // Interface Statistics Block: statistics of one interface, in its options
                    struct PcapngInterfaceStatisticsBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The interface the packet was received or transmitted on: the number of its Interface Description Block within the section
                        [[nodiscard]] std::uint32_t pcapng_interface_id() const noexcept { return little<std::uint32_t>(data + 0); }

                        // Upper 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_statistics_timestamp_upper() const noexcept { return little<std::uint32_t>(data + 4 + 0); }
                        // Lower 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_statistics_timestamp_lower() const noexcept { return little<std::uint32_t>(data + 4 + 4); }
                        // When the statistics were taken
                        [[nodiscard]] std::uint64_t pcapng_statistics_timestamp() const noexcept { return static_cast<std::uint64_t>(pcapng_statistics_timestamp_upper()) * UINT64_C(4294967296) + static_cast<std::uint64_t>(pcapng_statistics_timestamp_lower()); }

                        // One Interface Statistics Block option: its code, length and value
                        struct PcapngIsbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Interface Statistics Block's own
                            [[nodiscard]] std::uint16_t pcapng_isb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngIsbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngIsbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;

                                    // isb_starttime: when the capture started, in the Enhanced Packet Block timestamp form
                                    struct PcapngIsbStartTimeOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Upper 32 bits of the 64 bit timestamp
                                        [[nodiscard]] std::uint32_t pcapng_start_timestamp_upper() const noexcept { return little<std::uint32_t>(data + 0 + 0); }
                                        // Lower 32 bits of the 64 bit timestamp
                                        [[nodiscard]] std::uint32_t pcapng_start_timestamp_lower() const noexcept { return little<std::uint32_t>(data + 0 + 4); }
                                        // When the capture started
                                        [[nodiscard]] std::uint64_t pcapng_start_timestamp() const noexcept { return static_cast<std::uint64_t>(pcapng_start_timestamp_upper()) * UINT64_C(4294967296) + static_cast<std::uint64_t>(pcapng_start_timestamp_lower()); }
                                    };
                                    PcapngIsbStartTimeOption pcapng_isb_start_time_option;

                                    // isb_endtime: when the capture ended, in the Enhanced Packet Block timestamp form
                                    struct PcapngIsbEndTimeOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Upper 32 bits of the 64 bit timestamp
                                        [[nodiscard]] std::uint32_t pcapng_end_timestamp_upper() const noexcept { return little<std::uint32_t>(data + 0 + 0); }
                                        // Lower 32 bits of the 64 bit timestamp
                                        [[nodiscard]] std::uint32_t pcapng_end_timestamp_lower() const noexcept { return little<std::uint32_t>(data + 0 + 4); }
                                        // When the capture ended
                                        [[nodiscard]] std::uint64_t pcapng_end_timestamp() const noexcept { return static_cast<std::uint64_t>(pcapng_end_timestamp_upper()) * UINT64_C(4294967296) + static_cast<std::uint64_t>(pcapng_end_timestamp_lower()); }
                                    };
                                    PcapngIsbEndTimeOption pcapng_isb_end_time_option;

                                    // isb_ifrecv, isb_ifdrop, isb_filteraccept, isb_osdrop or isb_usrdeliv: a packet count, as its code says
                                    struct PcapngIsbCounterOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Packets counted since the start of the capture, as the option code says
                                        [[nodiscard]] std::uint64_t pcapng_isb_counter() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngIsbCounterOption pcapng_isb_counter_option;
                                };
                                PcapngIsbOptionContent pcapng_isb_option_content;
                            };
                            PcapngIsbOptionValue pcapng_isb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngIsbOption pcapng_isb_option;
                        std::size_t pcapng_isb_option_count = 0;   // entries read
                        std::size_t pcapng_isb_option_first = 0;   // where the first lies
                    };
                    PcapngInterfaceStatisticsBody pcapng_interface_statistics_body;

                    // Enhanced Packet Block: one captured packet, its interface, time and lengths, then its options
                    struct PcapngEnhancedPacketBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The interface the packet was received or transmitted on: the number of its Interface Description Block within the section
                        [[nodiscard]] std::uint32_t pcapng_interface_id() const noexcept { return little<std::uint32_t>(data + 0); }

                        // Upper 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_packet_timestamp_upper() const noexcept { return little<std::uint32_t>(data + 4 + 0); }
                        // Lower 32 bits of the 64 bit timestamp
                        [[nodiscard]] std::uint32_t pcapng_packet_timestamp_lower() const noexcept { return little<std::uint32_t>(data + 4 + 4); }
                        // When the packet was captured
                        [[nodiscard]] std::uint64_t pcapng_packet_timestamp() const noexcept { return static_cast<std::uint64_t>(pcapng_packet_timestamp_upper()) * UINT64_C(4294967296) + static_cast<std::uint64_t>(pcapng_packet_timestamp_lower()); }

                        // Octets captured from the packet: the length of Packet Data, without its padding
                        [[nodiscard]] std::uint32_t pcapng_captured_packet_length() const noexcept { return little<std::uint32_t>(data + 12); }

                        // Octets of the packet as it was transmitted on the network
                        [[nodiscard]] std::uint32_t pcapng_original_packet_length() const noexcept { return little<std::uint32_t>(data + 16); }

                        // The packet as captured, link-layer headers first, in the format of the interface's LinkType
                        std::size_t pcapng_packet_data_size = 0;
                        [[nodiscard]] const std::byte* pcapng_packet_data() const noexcept { return data + 20; }

                        std::size_t pcapng_packet_data_padding_at = 0;
                        // Zero octets bringing the packet data to a 32 bit boundary
                        std::size_t pcapng_packet_data_padding_size = 0;
                        [[nodiscard]] const std::byte* pcapng_packet_data_padding() const noexcept { return data + pcapng_packet_data_padding_at; }

                        // One Enhanced Packet Block option: its code, length and value
                        struct PcapngEpbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Enhanced Packet Block's own
                            [[nodiscard]] std::uint16_t pcapng_epb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngEpbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngEpbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;

                                    // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
                                    struct PcapngEpbFlags {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;
                                        // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
                                        [[nodiscard]] std::uint32_t pcapng_epb_flags() const noexcept { return little<std::uint32_t>(data + 0); }
                                        // Bits 0-1: inbound / outbound (00 information not available, 01 inbound, 10 outbound)
                                        [[nodiscard]] std::uint8_t pcapng_direction() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 0) & 0x3u); }
                                        // Bits 2-4: 000 not specified, 001 unicast, 010 multicast, 011 broadcast, 100 promiscuous
                                        [[nodiscard]] std::uint8_t pcapng_reception_type() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 2) & 0x7u); }
                                        // Bits 5-8: FCS length in octets, 0 when not available; overrides the interface's if_fcslen
                                        [[nodiscard]] std::uint8_t pcapng_fcs_length() const noexcept { return static_cast<std::uint8_t>((pcapng_epb_flags() >> 5) & 0xFu); }
                                        // Bit 9: checksum not ready, as a consequence of checksum offloading
                                        [[nodiscard]] bool pcapng_checksum_not_ready() const noexcept { return ((pcapng_epb_flags() >> 9) & 1u) != 0; }
                                        // Bit 10: the checksum was already checked on the receive path
                                        [[nodiscard]] bool pcapng_checksum_valid() const noexcept { return ((pcapng_epb_flags() >> 10) & 1u) != 0; }
                                        // Bit 11: TCP segmentation offloaded
                                        [[nodiscard]] bool pcapng_tcp_segmentation_offloaded() const noexcept { return ((pcapng_epb_flags() >> 11) & 1u) != 0; }
                                        // Bits 16-31: link-layer-dependent errors (31 symbol, 30 preamble, 29 start frame delimiter, 28 unaligned frame, 27 wrong inter frame gap, 26 packet too short, 25 packet too long, 24 CRC)
                                        [[nodiscard]] std::uint16_t pcapng_link_layer_errors() const noexcept { return static_cast<std::uint16_t>((pcapng_epb_flags() >> 16) & 0xFFFFu); }
                                    };
                                    PcapngEpbFlags pcapng_epb_flags;

                                    // epb_hash: a hash of the packet, which covers only the packet, not the capture driver's header
                                    struct PcapngEpbHashOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // The hashing algorithm, which gives the hash's size
                                        [[nodiscard]] std::uint8_t pcapng_hash_algorithm() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The hash of the packet
                                        std::size_t pcapng_hash_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_hash() const noexcept { return data + 1; }
                                    };
                                    PcapngEpbHashOption pcapng_epb_hash_option;

                                    // epb_dropcount: packets lost between this packet and the preceding one of the interface
                                    struct PcapngEpbDropCountOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Packets lost by the interface and the operating system between this packet and the preceding one for the same interface
                                        [[nodiscard]] std::uint64_t pcapng_drop_count() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngEpbDropCountOption pcapng_epb_drop_count_option;

                                    // epb_packetid: identifies the packet
                                    struct PcapngEpbPacketIdOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Uniquely identifies the packet; the same packet seen on several interfaces has the same id
                                        [[nodiscard]] std::uint64_t pcapng_packet_id() const noexcept { return little<std::uint64_t>(data + 0); }
                                    };
                                    PcapngEpbPacketIdOption pcapng_epb_packet_id_option;

                                    // epb_queue: the queue of the interface the packet was received on
                                    struct PcapngEpbQueueOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Queue of the interface the packet was received on
                                        [[nodiscard]] std::uint32_t pcapng_queue() const noexcept { return little<std::uint32_t>(data + 0); }
                                    };
                                    PcapngEpbQueueOption pcapng_epb_queue_option;

                                    // epb_verdict: what would be done with the packet after processing it
                                    struct PcapngEpbVerdictOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // The verdict type, which gives the verdict's size
                                        [[nodiscard]] std::uint8_t pcapng_verdict_type() const noexcept { return std::to_integer<std::uint8_t>(*(data + 0)); }

                                        // The verdict data, as its type says
                                        std::size_t pcapng_verdict_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_verdict() const noexcept { return data + 1; }
                                    };
                                    PcapngEpbVerdictOption pcapng_epb_verdict_option;

                                    // epb_processid_threadid: a process and thread that could have received or sent the packet
                                    struct PcapngEpbProcessIdThreadIdOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Process identifier; 0 when it cannot be determined
                                        [[nodiscard]] std::uint32_t pcapng_process_id() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // Thread identifier; 0 when it cannot be determined
                                        [[nodiscard]] std::uint32_t pcapng_thread_id() const noexcept { return little<std::uint32_t>(data + 4); }
                                    };
                                    PcapngEpbProcessIdThreadIdOption pcapng_epb_process_id_thread_id_option;
                                };
                                PcapngEpbOptionContent pcapng_epb_option_content;
                            };
                            PcapngEpbOptionValue pcapng_epb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngEpbOption pcapng_epb_option;
                        std::size_t pcapng_epb_option_count = 0;   // entries read
                        std::size_t pcapng_epb_option_first = 0;   // where the first lies
                    };
                    PcapngEnhancedPacketBody pcapng_enhanced_packet_body;

                    // Decryption Secrets Block: secrets for decrypting traffic in the file, then options
                    struct PcapngDecryptionSecretsBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // The format of the secrets
                        [[nodiscard]] std::uint32_t pcapng_secrets_type() const noexcept { return little<std::uint32_t>(data + 0); }

                        // Octets of the secrets, without padding
                        [[nodiscard]] std::uint32_t pcapng_secrets_length() const noexcept { return little<std::uint32_t>(data + 4); }

                        // The secrets, in the format Secrets Type says
                        std::size_t pcapng_secrets_data_size = 0;
                        [[nodiscard]] const std::byte* pcapng_secrets_data() const noexcept { return data + 8; }

                        std::size_t pcapng_secrets_padding_at = 0;
                        // Zero octets bringing the secrets to a 32 bit boundary
                        std::size_t pcapng_secrets_padding_size = 0;
                        [[nodiscard]] const std::byte* pcapng_secrets_padding() const noexcept { return data + pcapng_secrets_padding_at; }

                        // One Decryption Secrets Block option: its code, length and value
                        struct PcapngDsbOption {
                            const std::byte* data = nullptr;
                            std::size_t size = 0;

                            // The option's code: the common codes (3.5) and the Decryption Secrets Block's own
                            [[nodiscard]] std::uint16_t pcapng_dsb_option_code() const noexcept { return little<std::uint16_t>(data + 0); }

                            // Octets of the option's value, without its padding
                            [[nodiscard]] std::uint16_t pcapng_option_length() const noexcept { return little<std::uint16_t>(data + 2); }

                            // The option's value, as long as its Option Length says
                            struct PcapngDsbOptionValue {
                                const std::byte* data = nullptr;
                                std::size_t size = 0;

                                // Branch
                                struct PcapngDsbOptionContent {
                                    const std::byte* data = nullptr;
                                    std::size_t size = 0;

                                    // opt_comment: a comment on the block
                                    struct PcapngCommentOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // Human readable comment on the block, UTF-8, not zero terminated
                                        std::size_t pcapng_comment_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_comment() const noexcept { return data + 0; }
                                    };
                                    PcapngCommentOption pcapng_comment_option;

                                    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
                                    struct PcapngCustomTextOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data, a UTF-8 string, not zero terminated
                                        std::size_t pcapng_custom_text_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_text() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomTextOption pcapng_custom_text_option;

                                    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
                                    struct PcapngCustomDataOption {
                                        const std::byte* data = nullptr;
                                        std::size_t size = 0;

                                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                                        // The custom data
                                        std::size_t pcapng_custom_data_size = 0;
                                        [[nodiscard]] const std::byte* pcapng_custom_data() const noexcept { return data + 4; }
                                    };
                                    PcapngCustomDataOption pcapng_custom_data_option;
                                };
                                PcapngDsbOptionContent pcapng_dsb_option_content;
                            };
                            PcapngDsbOptionValue pcapng_dsb_option_value;

                            std::size_t pcapng_option_padding_at = 0;
                            // Zero octets bringing the option to a 32 bit boundary
                            std::size_t pcapng_option_padding_size = 0;
                            [[nodiscard]] const std::byte* pcapng_option_padding() const noexcept { return data + pcapng_option_padding_at; }
                        };
                        PcapngDsbOption pcapng_dsb_option;
                        std::size_t pcapng_dsb_option_count = 0;   // entries read
                        std::size_t pcapng_dsb_option_first = 0;   // where the first lies
                    };
                    PcapngDecryptionSecretsBody pcapng_decryption_secrets_body;

                    // Custom Block: vendor data identified by its enterprise number
                    struct PcapngCustomBody {
                        const std::byte* data = nullptr;
                        std::size_t size = 0;

                        // IANA Private Enterprise Number of the organization that defined the custom option or block
                        [[nodiscard]] std::uint32_t pcapng_private_enterprise_number() const noexcept { return little<std::uint32_t>(data + 0); }

                        // The custom data and any options, padded to 32 bits: where the data ends is known only to the vendor, so the rest of the body
                        std::size_t pcapng_custom_block_data_size = 0;
                        [[nodiscard]] const std::byte* pcapng_custom_block_data() const noexcept { return data + 4; }
                    };
                    PcapngCustomBody pcapng_custom_body;
                };
                PcapngBlockContent pcapng_block_content;
            };
            PcapngBlockBody pcapng_block_body;

            std::size_t pcapng_trailing_block_total_length_at = 0;
            // The Block Total Length repeated, to permit backward file navigation
            [[nodiscard]] std::uint32_t pcapng_trailing_block_total_length() const noexcept { return little<std::uint32_t>(data + pcapng_trailing_block_total_length_at); }
        };
        PcapngBlock pcapng_block;
        std::size_t pcapng_block_count = 0;   // entries read
        std::size_t pcapng_block_first = 0;   // where the first lies
    };

    PcapngFile pcapng_file;

    // read a Pcapng File
    bool read(const std::byte* data, std::size_t length) noexcept {
        return read_pcapng_file(data, length);
    }

    // Pcapng capture file: blocks, to the end of the file
    bool read_pcapng_file(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // General block structure (3.1): type, total length, body, total length again
        self.pcapng_block.data = nullptr;
        self.pcapng_block_count = 0;
        self.pcapng_block_first = offset;
        while (offset < limit) {
            if (!read_pcapng_block(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_block.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_block.size;
            ++self.pcapng_block_count;
        }
        self.size = offset;
        return true;
    }

    // General block structure (3.1): type, total length, body, total length again
    bool read_pcapng_block(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Identifies the block (10.1); values with the most significant bit set are reserved for local use
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Total size of the block in octets, a multiple of 4: 12 for a block with no body
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_total_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) < limit) { limit = static_cast<std::size_t>(stated); }
        }
        // The block's body: what its type says, padded to 32 bits
        if (!read_pcapng_block_body(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_block_body.size;
        // The Block Total Length repeated, to permit backward file navigation
        if (offset + 4 > limit) { self.size = offset; return false; }
        self.pcapng_trailing_block_total_length_at = offset;
        offset += 4;
        self.size = limit;
        return true;
    }

    // The block's body: what its type says, padded to 32 bits
    bool read_pcapng_block_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_total_length()) - INT64_C(12);
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_block_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_block_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_block_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_section_header_body.data = nullptr;
        self.pcapng_interface_description_body.data = nullptr;
        self.pcapng_packet_body.data = nullptr;
        self.pcapng_simple_packet_body.data = nullptr;
        self.pcapng_name_resolution_body.data = nullptr;
        self.pcapng_interface_statistics_body.data = nullptr;
        self.pcapng_enhanced_packet_body.data = nullptr;
        self.pcapng_decryption_secrets_body.data = nullptr;
        self.pcapng_custom_body.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(168627466))) {
            if (!read_pcapng_section_header_body(at, limit)) { return false; }
            self.size = self.pcapng_section_header_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(1))) {
            if (!read_pcapng_interface_description_body(at, limit)) { return false; }
            self.size = self.pcapng_interface_description_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(2))) {
            if (!read_pcapng_packet_body(at, limit)) { return false; }
            self.size = self.pcapng_packet_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(3))) {
            if (!read_pcapng_simple_packet_body(at, limit)) { return false; }
            self.size = self.pcapng_simple_packet_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(4))) {
            if (!read_pcapng_name_resolution_body(at, limit)) { return false; }
            self.size = self.pcapng_name_resolution_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(5))) {
            if (!read_pcapng_interface_statistics_body(at, limit)) { return false; }
            self.size = self.pcapng_interface_statistics_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(6))) {
            if (!read_pcapng_enhanced_packet_body(at, limit)) { return false; }
            self.size = self.pcapng_enhanced_packet_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(10))) {
            if (!read_pcapng_decryption_secrets_body(at, limit)) { return false; }
            self.size = self.pcapng_decryption_secrets_body.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_type()) == UINT64_C(1073744813))) {
            if (!read_pcapng_custom_body(at, limit)) { return false; }
            self.size = self.pcapng_custom_body.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // Section Header Block: byte order, version and length of the section, then its options
    bool read_pcapng_section_header_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // 1A2B3C4D in the byte order of the section: tells a little endian section from a big endian one
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Major version of the format: 1
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Minor version of the format: 0 (a reader treats 2 as 0)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the section after this Section Header Block, a multiple of 4; -1 when not specified
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        // One Section Header Block option: its code, length and value
        self.pcapng_shb_option.data = nullptr;
        self.pcapng_shb_option_count = 0;
        self.pcapng_shb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_shb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_shb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_shb_option.size;
            ++self.pcapng_shb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Section Header Block option: its code, length and value
    bool read_pcapng_shb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Section Header Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_shb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_shb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_shb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_shb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_shb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_shb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        self.pcapng_shb_hardware_option.data = nullptr;
        self.pcapng_shb_os_option.data = nullptr;
        self.pcapng_shb_user_application_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_shb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_shb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_shb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(2))) {
            if (!read_pcapng_shb_hardware_option(at, limit)) { return false; }
            self.size = self.pcapng_shb_hardware_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(3))) {
            if (!read_pcapng_shb_os_option(at, limit)) { return false; }
            self.size = self.pcapng_shb_os_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_code()) == UINT64_C(4))) {
            if (!read_pcapng_shb_user_application_option(at, limit)) { return false; }
            self.size = self.pcapng_shb_user_application_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_shb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_shb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_shb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Description of the hardware used to create this section
    bool read_pcapng_shb_hardware_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_shb_hardware_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Description of the hardware used to create this section, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_shb_hardware_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Name of the operating system used to create this section
    bool read_pcapng_shb_os_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_shb_os_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Name of the operating system used to create this section, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_shb_os_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Name of the application used to create this section
    bool read_pcapng_shb_user_application_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_shb_option_value.pcapng_shb_option_content.pcapng_shb_user_application_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Name of the application used to create this section, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_section_header_body.pcapng_shb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_shb_user_application_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Interface Description Block: an interface's link layer and snapshot length, then its options; interfaces are numbered from 0 in the order of their blocks within a section
    bool read_pcapng_interface_description_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Link layer type of the interface, from the PCAP-related LinkType registry (draft-ietf-opsawg-pcaplinktype)
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Not used: zero, ignored by readers
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Most octets captured from each packet; 0 for no limit
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // One Interface Description Block option: its code, length and value
        self.pcapng_idb_option.data = nullptr;
        self.pcapng_idb_option_count = 0;
        self.pcapng_idb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_idb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_idb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_idb_option.size;
            ++self.pcapng_idb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Interface Description Block option: its code, length and value
    bool read_pcapng_idb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Interface Description Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_idb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_idb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_idb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_idb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_idb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_idb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        self.pcapng_if_name_option.data = nullptr;
        self.pcapng_if_description_option.data = nullptr;
        self.pcapng_if_ipv4_address_option.data = nullptr;
        self.pcapng_if_ipv6_address_option.data = nullptr;
        self.pcapng_if_mac_address_option.data = nullptr;
        self.pcapng_if_eui_address_option.data = nullptr;
        self.pcapng_if_speed_option.data = nullptr;
        self.pcapng_if_timestamp_resolution.data = nullptr;
        self.pcapng_if_filter_option.data = nullptr;
        self.pcapng_if_os_option.data = nullptr;
        self.pcapng_if_fcs_length_option.data = nullptr;
        self.pcapng_if_timestamp_offset_option.data = nullptr;
        self.pcapng_if_hardware_option.data = nullptr;
        self.pcapng_if_transmit_speed_option.data = nullptr;
        self.pcapng_if_receive_speed_option.data = nullptr;
        self.pcapng_if_iana_time_zone_name_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_idb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_idb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_idb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(2))) {
            if (!read_pcapng_if_name_option(at, limit)) { return false; }
            self.size = self.pcapng_if_name_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(3))) {
            if (!read_pcapng_if_description_option(at, limit)) { return false; }
            self.size = self.pcapng_if_description_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(4))) {
            if (!read_pcapng_if_ipv4_address_option(at, limit)) { return false; }
            self.size = self.pcapng_if_ipv4_address_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(5))) {
            if (!read_pcapng_if_ipv6_address_option(at, limit)) { return false; }
            self.size = self.pcapng_if_ipv6_address_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(6))) {
            if (!read_pcapng_if_mac_address_option(at, limit)) { return false; }
            self.size = self.pcapng_if_mac_address_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(7))) {
            if (!read_pcapng_if_eui_address_option(at, limit)) { return false; }
            self.size = self.pcapng_if_eui_address_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(8))) {
            if (!read_pcapng_if_speed_option(at, limit)) { return false; }
            self.size = self.pcapng_if_speed_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(9))) {
            if (!read_pcapng_if_timestamp_resolution(at, limit)) { return false; }
            self.size = self.pcapng_if_timestamp_resolution.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(11))) {
            if (!read_pcapng_if_filter_option(at, limit)) { return false; }
            self.size = self.pcapng_if_filter_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(12))) {
            if (!read_pcapng_if_os_option(at, limit)) { return false; }
            self.size = self.pcapng_if_os_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(13))) {
            if (!read_pcapng_if_fcs_length_option(at, limit)) { return false; }
            self.size = self.pcapng_if_fcs_length_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(14))) {
            if (!read_pcapng_if_timestamp_offset_option(at, limit)) { return false; }
            self.size = self.pcapng_if_timestamp_offset_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(15))) {
            if (!read_pcapng_if_hardware_option(at, limit)) { return false; }
            self.size = self.pcapng_if_hardware_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(16))) {
            if (!read_pcapng_if_transmit_speed_option(at, limit)) { return false; }
            self.size = self.pcapng_if_transmit_speed_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(17))) {
            if (!read_pcapng_if_receive_speed_option(at, limit)) { return false; }
            self.size = self.pcapng_if_receive_speed_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_code()) == UINT64_C(18))) {
            if (!read_pcapng_if_iana_time_zone_name_option(at, limit)) { return false; }
            self.size = self.pcapng_if_iana_time_zone_name_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_idb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_idb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_idb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Name of the device used to capture data
    bool read_pcapng_if_name_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_name_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Name of the device used to capture data, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_name_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Description of the device used to capture data
    bool read_pcapng_if_description_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_description_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Description of the device used to capture data, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_description_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // if_IPv4addr: an IPv4 address and netmask, four octets each, not affected by the section's byte order
    bool read_pcapng_if_ipv4_address_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_ipv4_address_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IPv4 address of the interface, in network order
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Netmask of the address, in network order
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // if_IPv6addr: an IPv6 address and its prefix length
    bool read_pcapng_if_ipv6_address_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_ipv6_address_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IPv6 address of the interface, 16 octets in network order
        if (offset + 16 > limit) { self.size = offset; return false; }
        offset += 16;
        // Prefix length of the address, in bits
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // if_MACaddr: the interface hardware EUI-48 address
    bool read_pcapng_if_mac_address_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_mac_address_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Interface hardware EUI-48 (MAC) address
        if (offset + 6 > limit) { self.size = offset; return false; }
        offset += 6;
        self.size = offset;
        return true;
    }

    // if_EUIaddr: the interface hardware EUI-64 address
    bool read_pcapng_if_eui_address_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_eui_address_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Interface hardware EUI-64 address
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // if_speed: the interface speed
    bool read_pcapng_if_speed_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_speed_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Interface speed, bits per second
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // if_tsresol: the resolution of the interface's timestamps; 10^-6 s when absent
    bool read_pcapng_if_timestamp_resolution(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_timestamp_resolution;
        self.data = at;
        self.size = 0;
        if (available < 1) { return false; }
        self.size = 1;
        return true;
    }

    // if_filter: the filter used to capture traffic
    bool read_pcapng_if_filter_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_filter_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Code of the filter used, such as a libpcap string or BPF bytecode
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The filter, as its code says
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length()) - INT64_C(1);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_filter_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Name of the operating system of the machine the interface is installed in
    bool read_pcapng_if_os_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_os_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Name of the operating system of the machine the interface is installed in, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_os_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // if_fcslen: the length of the Frame Check Sequence for this interface
    bool read_pcapng_if_fcs_length_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_fcs_length_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Length of the Frame Check Sequence, in bits
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        self.size = offset;
        return true;
    }

    // if_tsoffset: an offset added to each packet's timestamp
    bool read_pcapng_if_timestamp_offset_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_timestamp_offset_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Seconds added to the timestamp of each packet to obtain its absolute timestamp; 0 when absent
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // Description of the interface hardware
    bool read_pcapng_if_hardware_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_hardware_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Description of the interface hardware, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_hardware_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // if_txspeed: the interface transmit speed
    bool read_pcapng_if_transmit_speed_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_transmit_speed_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Interface transmit speed, bits per second
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // if_rxspeed: the interface receive speed
    bool read_pcapng_if_receive_speed_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_receive_speed_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Interface receive speed, bits per second
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // IANA time zone database name of the interface's time zone
    bool read_pcapng_if_iana_time_zone_name_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_idb_option_value.pcapng_idb_option_content.pcapng_if_iana_time_zone_name_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA time zone database name of the interface's time zone, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_description_body.pcapng_idb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_if_iana_time_zone_name_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Packet Block: one captured packet, superseded by the Enhanced Packet Block
    bool read_pcapng_packet_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The interface the packet comes from, 16 bits
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // A local drop counter: packets lost between this packet and the preceding one; 0xFFFF when not available
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // When the packet was captured
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        // Octets captured from the packet: the length of Packet Data, without its padding
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Octets of the packet as it was transmitted on the network
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The packet as captured, link-layer headers first, in the format of the interface's LinkType
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_captured_packet_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_packet_data_size = bytes;
            offset += bytes;
        }
        // Zero octets bringing the packet data to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_packet_data_padding_at = offset; self.pcapng_packet_data_padding_size = bytes;
            offset += bytes;
        }
        // One Packet Block option: its code, length and value
        self.pcapng_pb_option.data = nullptr;
        self.pcapng_pb_option_count = 0;
        self.pcapng_pb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_pb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_pb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_pb_option.size;
            ++self.pcapng_pb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Packet Block option: its code, length and value
    bool read_pcapng_pb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Packet Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_pb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_pb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_pb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_pb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_pb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_pb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        self.pcapng_epb_flags.data = nullptr;
        self.pcapng_epb_hash_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_pb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_pb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_pb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(2))) {
            if (!read_pcapng_pb_option_content_pcapng_epb_flags(at, limit)) { return false; }
            self.size = self.pcapng_epb_flags.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_code()) == UINT64_C(3))) {
            if (!read_pcapng_pb_option_content_pcapng_epb_hash_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_hash_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_pb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_pb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_pb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
    bool read_pcapng_pb_option_content_pcapng_epb_flags(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content.pcapng_epb_flags;
        self.data = at;
        self.size = 0;
        if (available < 4) { return false; }
        self.size = 4;
        return true;
    }

    // epb_hash: a hash of the packet, which covers only the packet, not the capture driver's header
    bool read_pcapng_pb_option_content_pcapng_epb_hash_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_pb_option_value.pcapng_pb_option_content.pcapng_epb_hash_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The hashing algorithm, which gives the hash's size
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The hash of the packet
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_packet_body.pcapng_pb_option.pcapng_option_length()) - INT64_C(1);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_hash_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Simple Packet Block: one packet of interface 0, with only its original length
    bool read_pcapng_simple_packet_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_simple_packet_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Octets of the packet as it was transmitted on the network
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The packet, link-layer headers first: the rest of the body, the lesser of the interface's SnapLen and the original length followed by padding to 32 bits
        self.pcapng_simple_packet_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // Name Resolution Block: name resolution records to nrb_record_end, then options in the same Type - Length - Value form
    bool read_pcapng_name_resolution_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_name_resolution_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // One name resolution record, or after nrb_record_end one option (ns_dnsname 2, ns_dnsIP4addr 3, ns_dnsIP6addr 4, opt_comment 1): type, length, value padded to 32 bits
        self.pcapng_name_record.data = nullptr;
        self.pcapng_name_record_count = 0;
        self.pcapng_name_record_first = offset;
        while (offset < limit) {
            if (!read_pcapng_name_record(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_name_record.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_name_record.size;
            ++self.pcapng_name_record_count;
        }
        self.size = offset;
        return true;
    }

    // One name resolution record, or after nrb_record_end one option (ns_dnsname 2, ns_dnsIP4addr 3, ns_dnsIP6addr 4, opt_comment 1): type, length, value padded to 32 bits
    bool read_pcapng_name_record(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_name_resolution_body.pcapng_name_record;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The record type; after nrb_record_end, an option code
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The record's address followed by one or more zero terminated UTF-8 names (or an option's value); ns_dnsname is a UTF-8 string, ns_dnsIP4addr 4 and ns_dnsIP6addr 16 octets
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_name_resolution_body.pcapng_name_record.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_record_value_size = bytes;
            offset += bytes;
        }
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Interface Statistics Block: statistics of one interface, in its options
    bool read_pcapng_interface_statistics_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The interface the packet was received or transmitted on: the number of its Interface Description Block within the section
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // When the statistics were taken
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        // One Interface Statistics Block option: its code, length and value
        self.pcapng_isb_option.data = nullptr;
        self.pcapng_isb_option_count = 0;
        self.pcapng_isb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_isb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_isb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_isb_option.size;
            ++self.pcapng_isb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Interface Statistics Block option: its code, length and value
    bool read_pcapng_isb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Interface Statistics Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_isb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_isb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_isb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_isb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_isb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_isb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        self.pcapng_isb_start_time_option.data = nullptr;
        self.pcapng_isb_end_time_option.data = nullptr;
        self.pcapng_isb_counter_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_isb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_isb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_isb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(2))) {
            if (!read_pcapng_isb_start_time_option(at, limit)) { return false; }
            self.size = self.pcapng_isb_start_time_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(3))) {
            if (!read_pcapng_isb_end_time_option(at, limit)) { return false; }
            self.size = self.pcapng_isb_end_time_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(4)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(5)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(6)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(7)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_code()) == UINT64_C(8))) {
            if (!read_pcapng_isb_counter_option(at, limit)) { return false; }
            self.size = self.pcapng_isb_counter_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_isb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_isb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_isb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // isb_starttime: when the capture started, in the Enhanced Packet Block timestamp form
    bool read_pcapng_isb_start_time_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_isb_start_time_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // When the capture started
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // isb_endtime: when the capture ended, in the Enhanced Packet Block timestamp form
    bool read_pcapng_isb_end_time_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_isb_end_time_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // When the capture ended
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // isb_ifrecv, isb_ifdrop, isb_filteraccept, isb_osdrop or isb_usrdeliv: a packet count, as its code says
    bool read_pcapng_isb_counter_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_interface_statistics_body.pcapng_isb_option.pcapng_isb_option_value.pcapng_isb_option_content.pcapng_isb_counter_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Packets counted since the start of the capture, as the option code says
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // Enhanced Packet Block: one captured packet, its interface, time and lengths, then its options
    bool read_pcapng_enhanced_packet_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The interface the packet was received or transmitted on: the number of its Interface Description Block within the section
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // When the packet was captured
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        // Octets captured from the packet: the length of Packet Data, without its padding
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Octets of the packet as it was transmitted on the network
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The packet as captured, link-layer headers first, in the format of the interface's LinkType
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_captured_packet_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_packet_data_size = bytes;
            offset += bytes;
        }
        // Zero octets bringing the packet data to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_packet_data_padding_at = offset; self.pcapng_packet_data_padding_size = bytes;
            offset += bytes;
        }
        // One Enhanced Packet Block option: its code, length and value
        self.pcapng_epb_option.data = nullptr;
        self.pcapng_epb_option_count = 0;
        self.pcapng_epb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_epb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_epb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_epb_option.size;
            ++self.pcapng_epb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Enhanced Packet Block option: its code, length and value
    bool read_pcapng_epb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Enhanced Packet Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_epb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_epb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_epb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_epb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_epb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_epb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        self.pcapng_epb_flags.data = nullptr;
        self.pcapng_epb_hash_option.data = nullptr;
        self.pcapng_epb_drop_count_option.data = nullptr;
        self.pcapng_epb_packet_id_option.data = nullptr;
        self.pcapng_epb_queue_option.data = nullptr;
        self.pcapng_epb_verdict_option.data = nullptr;
        self.pcapng_epb_process_id_thread_id_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_epb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_epb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_epb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(2))) {
            if (!read_pcapng_epb_option_content_pcapng_epb_flags(at, limit)) { return false; }
            self.size = self.pcapng_epb_flags.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(3))) {
            if (!read_pcapng_epb_option_content_pcapng_epb_hash_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_hash_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(4))) {
            if (!read_pcapng_epb_drop_count_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_drop_count_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(5))) {
            if (!read_pcapng_epb_packet_id_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_packet_id_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(6))) {
            if (!read_pcapng_epb_queue_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_queue_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(7))) {
            if (!read_pcapng_epb_verdict_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_verdict_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_code()) == UINT64_C(8))) {
            if (!read_pcapng_epb_process_id_thread_id_option(at, limit)) { return false; }
            self.size = self.pcapng_epb_process_id_thread_id_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_epb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_epb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_epb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // epb_flags: the Enhanced Packet Block flags word, least significant bit first (4.3.1)
    bool read_pcapng_epb_option_content_pcapng_epb_flags(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_flags;
        self.data = at;
        self.size = 0;
        if (available < 4) { return false; }
        self.size = 4;
        return true;
    }

    // epb_hash: a hash of the packet, which covers only the packet, not the capture driver's header
    bool read_pcapng_epb_option_content_pcapng_epb_hash_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_hash_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The hashing algorithm, which gives the hash's size
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The hash of the packet
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length()) - INT64_C(1);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_hash_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // epb_dropcount: packets lost between this packet and the preceding one of the interface
    bool read_pcapng_epb_drop_count_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_drop_count_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Packets lost by the interface and the operating system between this packet and the preceding one for the same interface
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // epb_packetid: identifies the packet
    bool read_pcapng_epb_packet_id_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_packet_id_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Uniquely identifies the packet; the same packet seen on several interfaces has the same id
        if (offset + 8 > limit) { self.size = offset; return false; }
        offset += 8;
        self.size = offset;
        return true;
    }

    // epb_queue: the queue of the interface the packet was received on
    bool read_pcapng_epb_queue_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_queue_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Queue of the interface the packet was received on
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // epb_verdict: what would be done with the packet after processing it
    bool read_pcapng_epb_verdict_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_verdict_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The verdict type, which gives the verdict's size
        if (offset + 1 > limit) { self.size = offset; return false; }
        offset += 1;
        // The verdict data, as its type says
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_option_length()) - INT64_C(1);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_verdict_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // epb_processid_threadid: a process and thread that could have received or sent the packet
    bool read_pcapng_epb_process_id_thread_id_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_enhanced_packet_body.pcapng_epb_option.pcapng_epb_option_value.pcapng_epb_option_content.pcapng_epb_process_id_thread_id_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Process identifier; 0 when it cannot be determined
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Thread identifier; 0 when it cannot be determined
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        self.size = offset;
        return true;
    }

    // Decryption Secrets Block: secrets for decrypting traffic in the file, then options
    bool read_pcapng_decryption_secrets_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The format of the secrets
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // Octets of the secrets, without padding
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The secrets, in the format Secrets Type says
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_secrets_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_secrets_data_size = bytes;
            offset += bytes;
        }
        // Zero octets bringing the secrets to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_secrets_padding_at = offset; self.pcapng_secrets_padding_size = bytes;
            offset += bytes;
        }
        // One Decryption Secrets Block option: its code, length and value
        self.pcapng_dsb_option.data = nullptr;
        self.pcapng_dsb_option_count = 0;
        self.pcapng_dsb_option_first = offset;
        while (offset < limit) {
            if (!read_pcapng_dsb_option(at + offset, limit - offset)) { self.size = offset; return false; }
            if (self.pcapng_dsb_option.size == 0) { self.size = offset; return false; }
            offset += self.pcapng_dsb_option.size;
            ++self.pcapng_dsb_option_count;
        }
        self.size = offset;
        return true;
    }

    // One Decryption Secrets Block option: its code, length and value
    bool read_pcapng_dsb_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // The option's code: the common codes (3.5) and the Decryption Secrets Block's own
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // Octets of the option's value, without its padding
        if (offset + 2 > limit) { self.size = offset; return false; }
        offset += 2;
        // The option's value, as long as its Option Length says
        if (!read_pcapng_dsb_option_value(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_dsb_option_value.size;
        // Zero octets bringing the option to a 32 bit boundary
        {
            const std::size_t bytes = (4 - offset % 4) % 4;
            if (bytes > limit - offset) { self.size = offset; return false; }
            self.pcapng_option_padding_at = offset; self.pcapng_option_padding_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // The option's value, as long as its Option Length says
    bool read_pcapng_dsb_option_value(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_value;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_option_length());
            if (stated < 0 || static_cast<std::size_t>(stated) < offset) { self.size = offset; return false; }
            if (static_cast<std::size_t>(stated) > limit) { self.size = offset; return false; }
            limit = static_cast<std::size_t>(stated);
        }
        // Branch
        if (!read_pcapng_dsb_option_content(at + offset, limit - offset)) { self.size = offset; return false; }
        offset += self.pcapng_dsb_option_content.size;
        self.size = limit;
        return true;
    }

    // Branch
    bool read_pcapng_dsb_option_content(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_value.pcapng_dsb_option_content;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        self.pcapng_comment_option.data = nullptr;
        self.pcapng_custom_text_option.data = nullptr;
        self.pcapng_custom_data_option.data = nullptr;
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_code()) == UINT64_C(1))) {
            if (!read_pcapng_dsb_option_content_pcapng_comment_option(at, limit)) { return false; }
            self.size = self.pcapng_comment_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_code()) == UINT64_C(2988)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_code()) == UINT64_C(19372))) {
            if (!read_pcapng_dsb_option_content_pcapng_custom_text_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_text_option.size;
            return true;
        }
        if ((this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_code()) == UINT64_C(2989)) || (this->pcapng_file.pcapng_block.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.data != nullptr && this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.data != nullptr && static_cast<std::uint64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_code()) == UINT64_C(19373))) {
            if (!read_pcapng_dsb_option_content_pcapng_custom_data_option(at, limit)) { return false; }
            self.size = self.pcapng_custom_data_option.size;
            return true;
        }
        self.size = 0;
        return true;
    }

    // opt_comment: a comment on the block
    bool read_pcapng_dsb_option_content_pcapng_comment_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_value.pcapng_dsb_option_content.pcapng_comment_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // Human readable comment on the block, UTF-8, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_option_length());
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_comment_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2988 or 19372: vendor data as a UTF-8 string (3.5.1)
    bool read_pcapng_dsb_option_content_pcapng_custom_text_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_value.pcapng_dsb_option_content.pcapng_custom_text_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data, a UTF-8 string, not zero terminated
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_text_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // opt_custom 2989 or 19373: vendor data as octets (3.5.1)
    bool read_pcapng_dsb_option_content_pcapng_custom_data_option(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_dsb_option_value.pcapng_dsb_option_content.pcapng_custom_data_option;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data
        {
            const std::int64_t stated = static_cast<std::int64_t>(this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_decryption_secrets_body.pcapng_dsb_option.pcapng_option_length()) - INT64_C(4);
            if (stated < 0) { self.size = offset; return false; }
            std::size_t bytes = static_cast<std::size_t>(stated);
            if (bytes > limit - offset) { bytes = limit - offset; }
            self.pcapng_custom_data_size = bytes;
            offset += bytes;
        }
        self.size = offset;
        return true;
    }

    // Custom Block: vendor data identified by its enterprise number
    bool read_pcapng_custom_body(const std::byte* at, std::size_t available) noexcept {
        auto& self = this->pcapng_file.pcapng_block.pcapng_block_body.pcapng_block_content.pcapng_custom_body;
        self.data = at;
        self.size = 0;
        std::size_t limit = available;
        std::size_t offset = 0;
        // IANA Private Enterprise Number of the organization that defined the custom option or block
        if (offset + 4 > limit) { self.size = offset; return false; }
        offset += 4;
        // The custom data and any options, padded to 32 bits: where the data ends is known only to the vendor, so the rest of the body
        self.pcapng_custom_block_data_size = limit - offset;
        offset = limit;
        self.size = offset;
        return true;
    }

    // the bytes a Pcapng Block must hold before its length is known
    static constexpr std::size_t pcapng_block_header = 8;

    // how long a Pcapng Block is, read from its first pcapng_block_header bytes
    [[nodiscard]] static std::int64_t pcapng_block_length(const std::byte* at) noexcept {
        return static_cast<std::int64_t>(little<std::uint32_t>(at + 4));
    }
};

}
