#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

class Visitor;

// Options Only. The Transaction Begin message indicates any subsequent messages, up to the
// accompanying Transaction End message, are all part of the same transaction block. All PITCH
// messages corresponding to such an event would be included between a Transaction Begin
// message and Transaction End message. It is important to note that transaction blocks are
// currently used in US Options for symbol state transitions only, but may be expanded to other
// use cases with notice. Transaction Begin messages do not alter the book and can be ignored
// if messages are being used solely to build a book.
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

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
