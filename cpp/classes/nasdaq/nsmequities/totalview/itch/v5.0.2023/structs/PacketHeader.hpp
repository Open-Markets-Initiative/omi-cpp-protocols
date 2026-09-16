#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Itch Mold Udp 64 Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 20;

    PacketHeader() = default;
    PacketHeader(const std::string& session, std::uint64_t sequence_number, std::uint16_t message_count);

    // Session: Identity of the multicast session
    const std::string& session() const;
    std::string& session();
    void set_session(const std::string& value);

    // Sequence Number: Sequence number of the first message to follow this header
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Message Count: Number of messages to follow this header
    std::uint16_t message_count() const;
    void set_message_count(std::uint16_t value);

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
    std::string session_{};
    std::uint64_t sequence_number_{};
    std::uint16_t message_count_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
