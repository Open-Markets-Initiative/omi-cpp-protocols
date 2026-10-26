#pragma once

#include <array>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/TcpMessage.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class TcpMessageVisitor;

// Tcp message response carrying tag data including their packet headers in response to a
// retransmission or snapshot request.
class MessageResponseMessage : public TcpMessage {
  public:
    // The code that selects this message
    static constexpr TcpMessageCode message_type = PacketType::MessageResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 0;

    MessageResponseMessage() = default;
    MessageResponseMessage(const std::array<std::byte, 0>& data);

    // Data: Variable length payload of FLEX tags including their packet headers
    const std::array<std::byte, 0>& data() const;
    std::array<std::byte, 0>& data();
    void set_data(const std::array<std::byte, 0>& value);

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

    bool operator==(const MessageResponseMessage& other) const;
    bool operator!=(const MessageResponseMessage& other) const;

  private:
    std::array<std::byte, 0> data_{};
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
