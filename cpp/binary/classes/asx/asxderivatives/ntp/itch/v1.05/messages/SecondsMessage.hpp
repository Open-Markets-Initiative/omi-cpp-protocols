#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// A ‘seconds’ Nanoseconds is issued every second and any message thereafter will be stamped
// with the number of nanoseconds past the last Time message received as a time reference point
class SecondsMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecondsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SecondsMessage() = default;
    SecondsMessage(std::chrono::seconds second);

    // Second: Unix time (number of seconds since 1970-01-01 00:00:00 UTC).
    std::chrono::seconds second() const;
    void set_second(std::chrono::seconds value);

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
    std::chrono::seconds second_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
