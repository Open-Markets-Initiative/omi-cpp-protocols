#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Transaction Begin message indicates any subsequent messages, up to the accompanying
// Transaction End message, are all part of the same transaction block.
class TransactionBeginMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TransactionBeginMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TransactionBeginMessage() = default;
    TransactionBeginMessage(std::chrono::nanoseconds time_offset);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

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

    bool operator==(const TransactionBeginMessage& other) const;
    bool operator!=(const TransactionBeginMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
