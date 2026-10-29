#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class SequencedMessageVisitor;

// Reflects the number of seconds past midnight that the Timestamp message was generated.
class SecondsMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::TimestampSecondsMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    SecondsMessage() = default;
    SecondsMessage(std::chrono::seconds seconds);

    // Seconds: Number of seconds since midnight of the day that the trading session started.
    std::chrono::seconds seconds() const;
    void set_seconds(std::chrono::seconds value);
    std::int64_t seconds_utc(const calendar::Day& day) const;

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const SecondsMessage& other) const;
    bool operator!=(const SecondsMessage& other) const;

  private:
    std::chrono::seconds seconds_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
