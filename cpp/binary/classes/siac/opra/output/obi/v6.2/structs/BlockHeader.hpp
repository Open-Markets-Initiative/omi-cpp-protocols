#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/DataFeedIndicator.hpp"
#include "../enums/RetransmissionIndicator.hpp"
#include "../enums/SessionIndicator.hpp"
#include "../structs/BlockTimestamp.hpp"

namespace siac::opra::output::obi::v6_2 {

// Opra packet header
class BlockHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 21;

    BlockHeader() = default;
    BlockHeader(std::uint8_t version, std::uint16_t block_size, DataFeedIndicator data_feed_indicator, RetransmissionIndicator retransmission_indicator, SessionIndicator session_indicator, std::uint32_t block_sequence_number, std::uint8_t messages_in_block, const BlockTimestamp& block_timestamp, std::uint16_t block_checksum);

    // Version: Designates the OPRA binary version
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Block Size: Size in bytes of entire transmission block
    std::uint16_t block_size() const;
    void set_block_size(std::uint16_t value);

    // Data Feed Indicator: Value is ‘O’ for OPRA
    DataFeedIndicator data_feed_indicator() const;
    void set_data_feed_indicator(DataFeedIndicator value);

    // Retransmission Indicator: Contains either a space; not a retransmitted message or V;
    // indicating a retransmission of the block.
    RetransmissionIndicator retransmission_indicator() const;
    void set_retransmission_indicator(RetransmissionIndicator value);

    // Session Indicator: 0x00 for regular trading session
    SessionIndicator session_indicator() const;
    void set_session_indicator(SessionIndicator value);

    // Block Sequence Number: Packet Sequence Number
    std::uint32_t block_sequence_number() const;
    void set_block_sequence_number(std::uint32_t value);

    // Messages In Block: The number of messages contained in the block data of the
    // transmission block.
    std::uint8_t messages_in_block() const;
    void set_messages_in_block(std::uint8_t value);

    // Block Timestamp: Opra packet timestamp
    const BlockTimestamp& block_timestamp() const;
    BlockTimestamp& block_timestamp();
    void set_block_timestamp(const BlockTimestamp& value);

    // Block Checksum: Lower 16 bits of the 32 bit sum of all bytes in the block, excluding the
    // Block Checksum field
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
    DataFeedIndicator data_feed_indicator_{};
    RetransmissionIndicator retransmission_indicator_{};
    SessionIndicator session_indicator_{};
    std::uint32_t block_sequence_number_{};
    std::uint8_t messages_in_block_{};
    BlockTimestamp block_timestamp_{};
    std::uint16_t block_checksum_{};
};

std::ostream& operator<<(std::ostream& out, const BlockHeader& value);

} // namespace siac::opra::output::obi::v6_2
