#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class SequencedMessageVisitor;

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken. An execution may
// be broken if it is found to be “clearly erroneous” pursuant to NASDAQ’s Clearly Erroneous
// Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
class BrokenTradeOrderExecutedMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::BrokenTradeOrderExecutedMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    BrokenTradeOrderExecutedMessage() = default;
    BrokenTradeOrderExecutedMessage(std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint32_t cross_number, std::uint32_t match_number);

    // Tracking Number: Nasdaq Internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Timestamp: Nanoseconds since midnight
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // Cross Number: Trade Group Id. Ties together all trades of a given atomic transaction in
    // the matching engine.
    std::uint32_t cross_number() const;
    void set_cross_number(std::uint32_t value);

    // Match Number: Execution Id. Identifies the component of an execution. Unique for a given
    // day. The match number is also referenced in the Trade Break Message.
    std::uint32_t match_number() const;
    void set_match_number(std::uint32_t value);

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

    bool operator==(const BrokenTradeOrderExecutedMessage& other) const;
    bool operator!=(const BrokenTradeOrderExecutedMessage& other) const;

  private:
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t cross_number_{};
    std::uint32_t match_number_{};
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
