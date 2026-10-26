#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// Tcp end of message marker terminating a retransmission or snapshot session.
class EndOfMessageMessage : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = PacketType::EndOfMessageMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 6;

    EndOfMessageMessage() = default;
    EndOfMessageMessage(std::uint8_t multicast_group_number, std::uint8_t number_of_system_reboots, std::uint32_t next_sequence_number);

    // Multicast Group Number: Multicast Group Number for the request target
    std::uint8_t multicast_group_number() const;
    void set_multicast_group_number(std::uint8_t value);

    // Number Of System Reboots: For retransmission set to the number of times the system has
    // been rebooted; for snapshot set to 0
    std::uint8_t number_of_system_reboots() const;
    void set_number_of_system_reboots(std::uint8_t value);

    // Next Sequence Number: For retransmission set to 0; for snapshot indicates the next
    // multicast transmission sequence number that should be received after capturing the
    // snapshot
    std::uint32_t next_sequence_number() const;
    void set_next_sequence_number(std::uint32_t value);

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

    bool operator==(const EndOfMessageMessage& other) const;
    bool operator!=(const EndOfMessageMessage& other) const;

  private:
    std::uint8_t multicast_group_number_{};
    std::uint8_t number_of_system_reboots_{};
    std::uint32_t next_sequence_number_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
