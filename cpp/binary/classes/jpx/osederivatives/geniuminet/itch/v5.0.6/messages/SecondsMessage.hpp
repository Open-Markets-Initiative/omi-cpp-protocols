#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class Visitor;

// Sent every second for which at least one ITCH message is being generated
class SecondsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecondsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SecondsMessage() = default;
    SecondsMessage(std::chrono::seconds seconds);

    // Seconds: Unix time (seconds since 1970-01-01 00:00:00 UTC)
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);

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

    bool operator==(const SecondsMessage& other) const;
    bool operator!=(const SecondsMessage& other) const;

  private:
    std::chrono::seconds seconds_{};
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
