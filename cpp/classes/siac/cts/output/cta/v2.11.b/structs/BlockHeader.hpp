#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../structs/SipBlockTimestamp.hpp"

namespace siac::cts::output::cta::v2_11_b {

// Cta Output packet header
class BlockHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 20;

    BlockHeader() = default;
    BlockHeader(std::uint8_t version, std::uint16_t block_size, char data_feed_indicator, char retransmission_indicator, std::uint32_t block_sequence_number, std::uint8_t messages_in_block, const SipBlockTimestamp& sip_block_timestamp, std::uint16_t block_checksum);

    // Version: Designates The Cta Binary Version
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Block Size: Size In Bytes Of Entire Transmission Block
    std::uint16_t block_size() const;
    void set_block_size(std::uint16_t value);

    // Data Feed Indicator: Data Feed Indicator
    char data_feed_indicator() const;
    void set_data_feed_indicator(char value);

    // Retransmission Indicator: Retransmission Indicator
    char retransmission_indicator() const;
    void set_retransmission_indicator(char value);

    // Block Sequence Number: Packet Sequence Number
    std::uint32_t block_sequence_number() const;
    void set_block_sequence_number(std::uint32_t value);

    // Messages In Block: The Number Of Messages Contained In The Block Data Of The
    // Transmission Block
    std::uint8_t messages_in_block() const;
    void set_messages_in_block(std::uint8_t value);

    // SIP Block Timestamp: Cta packet timestamp
    const SipBlockTimestamp& sip_block_timestamp() const;
    SipBlockTimestamp& sip_block_timestamp();
    void set_sip_block_timestamp(const SipBlockTimestamp& value);

    // Block Checksum: Lower 16 Bits Of The 32 Bit Sum Of All Bytes In The Block Excluding The
    // Block Checksum Field
    std::uint16_t block_checksum() const;
    void set_block_checksum(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BlockHeader& other) const;
    bool operator!=(const BlockHeader& other) const;

  private:
    std::uint8_t version_{};
    std::uint16_t block_size_{};
    char data_feed_indicator_{};
    char retransmission_indicator_{};
    std::uint32_t block_sequence_number_{};
    std::uint8_t messages_in_block_{};
    SipBlockTimestamp sip_block_timestamp_{};
    std::uint16_t block_checksum_{};
};

std::ostream& operator<<(std::ostream& out, const BlockHeader& value);

} // namespace siac::cts::output::cta::v2_11_b
