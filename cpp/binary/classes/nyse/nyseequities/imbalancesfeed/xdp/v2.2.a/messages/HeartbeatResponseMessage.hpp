#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

class Visitor;

// Clients who remain connected to the Retransmission Server intraday must respond to a
// Heartbeat with a Heartbeat Response message within 5 seconds. If no timely client response
// is received, the connection will be closed.
class HeartbeatResponseMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::HeartbeatResponseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    HeartbeatResponseMessage() = default;
    HeartbeatResponseMessage(const std::string& source_id);

    // Source Id: The ID of the client requesting this retransmission . This field is up to 9
    // characters, null terminated.
    const std::string& source_id() const;
    std::string& source_id();
    void set_source_id(const std::string& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const HeartbeatResponseMessage& other) const;
    bool operator!=(const HeartbeatResponseMessage& other) const;

  private:
    std::string source_id_{};
};

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
