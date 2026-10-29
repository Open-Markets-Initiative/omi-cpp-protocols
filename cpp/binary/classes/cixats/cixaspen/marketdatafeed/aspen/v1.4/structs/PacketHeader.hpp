#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

#include "../enums/FeedIdentifier.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 20;

    PacketHeader() = default;
    PacketHeader(const std::string& market_day_identifier, FeedIdentifier feed_identifier, std::uint64_t sequence, std::uint16_t count);

    // Market Day Identifier: Unique identifier for trading day
    const std::string& market_day_identifier() const;
    std::string& market_day_identifier();
    void set_market_day_identifier(const std::string& value);

    // Feed Identifier: Unique code for feed
    FeedIdentifier feed_identifier() const;
    void set_feed_identifier(FeedIdentifier value);

    // Sequence: Sequence number for next message
    std::uint64_t sequence() const;
    void set_sequence(std::uint64_t value);

    // Count: Number of messages in packet
    std::uint16_t count() const;
    void set_count(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PacketHeader& other) const;
    bool operator!=(const PacketHeader& other) const;

  private:
    std::string market_day_identifier_{};
    FeedIdentifier feed_identifier_{};
    std::uint64_t sequence_{};
    std::uint16_t count_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
