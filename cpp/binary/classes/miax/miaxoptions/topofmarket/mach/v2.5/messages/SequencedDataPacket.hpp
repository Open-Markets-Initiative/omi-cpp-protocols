#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

class TcpMessageVisitor;

// The SesM server uses Sequenced data packets to send all messages that must be recoverable by
// the client in case of a connection loss
class SequencedDataPacket : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = SesmPacketType::SequencedDataPacket;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    SequencedDataPacket() = default;
    SequencedDataPacket(std::uint64_t sequence_number, std::uint8_t matching_engine_id, char sequenced_message_type, const std::array<std::byte, 0>& sequenced_message);

    // Sequence Number: Original sequence number from the live feed.
    std::uint64_t sequence_number() const;
    void set_sequence_number(std::uint64_t value);

    // Matching Engine Id: Matching Engine that originated the packet
    std::uint8_t matching_engine_id() const;
    void set_matching_engine_id(std::uint8_t value);

    // Sequenced Message Type: Market-data application message type carried over the SesM
    // sequenced channel (matches the MACH UDP Message Type byte; Miax Options uses Ascii
    // message codes)
    char sequenced_message_type() const;
    void set_sequenced_message_type(char value);

    // Sequenced Message:
    const std::array<std::byte, 0>& sequenced_message() const;
    std::array<std::byte, 0>& sequenced_message();
    void set_sequenced_message(const std::array<std::byte, 0>& value);

    // TcpMessage
    TcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TcpMessageVisitor& visitor) const override;
    std::unique_ptr<TcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TcpMessage& other) const override;

    bool operator==(const SequencedDataPacket& other) const;
    bool operator!=(const SequencedDataPacket& other) const;

  private:
    std::uint64_t sequence_number_{};
    std::uint8_t matching_engine_id_{};
    char sequenced_message_type_{};
    std::array<std::byte, 0> sequenced_message_{};
};

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
