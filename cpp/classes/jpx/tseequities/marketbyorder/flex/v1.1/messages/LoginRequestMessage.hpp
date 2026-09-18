#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// Tcp login request for retransmission or snapshot. Packet Type R selects retransmission and L
// selects snapshot.
class LoginRequestMessage : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = PacketType::LoginRequestMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 15;

    LoginRequestMessage() = default;
    LoginRequestMessage(const std::string& user_id, std::uint8_t multicast_group_number, std::uint8_t number_of_system_reboots, std::uint32_t sequence_number, std::uint32_t requested_message_count);

    // User Id: User ID for login authentication
    const std::string& user_id() const;
    std::string& user_id();
    void set_user_id(const std::string& value);

    // Multicast Group Number: Multicast Group Number for the request target
    std::uint8_t multicast_group_number() const;
    void set_multicast_group_number(std::uint8_t value);

    // Number Of System Reboots: For retransmission set to the number of times the system has
    // been rebooted; for snapshot set to 0
    std::uint8_t number_of_system_reboots() const;
    void set_number_of_system_reboots(std::uint8_t value);

    // Sequence Number: For retransmission set to the first sequence number for the request;
    // for snapshot set to 0
    std::uint32_t sequence_number() const;
    void set_sequence_number(std::uint32_t value);

    // Requested Message Count: For retransmission set to the number of messages from the first
    // sequence number; for snapshot set to 0
    std::uint32_t requested_message_count() const;
    void set_requested_message_count(std::uint32_t value);

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

    bool operator==(const LoginRequestMessage& other) const;
    bool operator!=(const LoginRequestMessage& other) const;

  private:
    std::string user_id_{};
    std::uint8_t multicast_group_number_{};
    std::uint8_t number_of_system_reboots_{};
    std::uint32_t sequence_number_{};
    std::uint32_t requested_message_count_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
