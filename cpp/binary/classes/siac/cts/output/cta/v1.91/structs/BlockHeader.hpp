#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/RetransmissionIndicator.hpp"
#include "../structs/SipBlockTimestamp.hpp"

namespace siac::cts::output::cta::v1_91 {

// Cta Output packet header
class BlockHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 20;

    BlockHeader() = default;
    BlockHeader(std::uint8_t version, std::uint16_t block_size, char data_feed_indicator, RetransmissionIndicator retransmission_indicator, std::uint32_t block_sequence_number, std::uint8_t messages_in_block, const SipBlockTimestamp& sip_block_timestamp, std::uint16_t block_checksum);

    // Version: CQS binary protocol version
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Block Size: Indicate size in bytes of the entire transmission bloc
    std::uint16_t block_size() const;
    void set_block_size(std::uint16_t value);

    // Data Feed Indicator: Q for Consolidated Quotation System
    char data_feed_indicator() const;
    void set_data_feed_indicator(char value);

    // Retransmission Indicator: Indicates an original message or a retransmitted block
    RetransmissionIndicator retransmission_indicator() const;
    void set_retransmission_indicator(RetransmissionIndicator value);

    // Block Sequence Number: All transmission blocks are assigned a sequential Block Sequence
    // Number
    std::uint32_t block_sequence_number() const;
    void set_block_sequence_number(std::uint32_t value);

    // Messages In Block: The number of messages contained in the transmission block
    std::uint8_t messages_in_block() const;
    void set_messages_in_block(std::uint8_t value);

    // Sip Block Timestamp: Sip Block Timestamp
    const SipBlockTimestamp& sip_block_timestamp() const;
    SipBlockTimestamp& sip_block_timestamp();
    void set_sip_block_timestamp(const SipBlockTimestamp& value);

    // Block Checksum: Lower 2 bytes of the 4 byte sum of all the bytes in the block, excluding
    // this Block Checksum field
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
    RetransmissionIndicator retransmission_indicator_{};
    std::uint32_t block_sequence_number_{};
    std::uint8_t messages_in_block_{};
    SipBlockTimestamp sip_block_timestamp_{};
    std::uint16_t block_checksum_{};
};

std::ostream& operator<<(std::ostream& out, const BlockHeader& value);

} // namespace siac::cts::output::cta::v1_91
