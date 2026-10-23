#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// This message disseminates free text information describing ad-hoc market events
class TextMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TextMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 112;

    TextMessage() = default;
    TextMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, const std::string& source_id, const std::string& text);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Source Id: Indicates source of message.
    const std::string& source_id() const;
    std::string& source_id();
    void set_source_id(const std::string& value);

    // Text: Message being communicated.
    const std::string& text() const;
    std::string& text();
    void set_text(const std::string& value);

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

    bool operator==(const TextMessage& other) const;
    bool operator!=(const TextMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::string source_id_{};
    std::string text_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
