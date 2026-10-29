#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// Reflects the number of seconds past midnight that the Timestamp message was generated.
class TimestampMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'T';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    TimestampMessage() = default;
    TimestampMessage(std::chrono::seconds second);

    // Second: Number of seconds since midnight.
    std::chrono::seconds second() const;
    void set_second(std::chrono::seconds value);
    std::int64_t second_utc(const calendar::Day& day) const;

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

    bool operator==(const TimestampMessage& other) const;
    bool operator!=(const TimestampMessage& other) const;

  private:
    std::chrono::seconds second_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
