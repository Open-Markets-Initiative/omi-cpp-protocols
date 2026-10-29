#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

class Visitor;

// The Transaction End message indicates that a transaction indicated by a previous Transaction
// Begin message has completed.
class TransactionEndMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TransactionEndMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TransactionEndMessage() = default;
    TransactionEndMessage(std::chrono::nanoseconds time_offset);

    // Time Offset: Nanosecond offset from last unit timestamp
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

    bool operator==(const TransactionEndMessage& other) const;
    bool operator!=(const TransactionEndMessage& other) const;

  private:
    std::chrono::nanoseconds time_offset_{};
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
